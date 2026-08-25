#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <HardwareSerial.h>

#define CURRENT_FIRMWARE_VERSION "1.0.0"
#define EXPECTED_TOKEN "aya_token_2025"

#define JSON_URL "https://raw.githubusercontent.com/yourusername/yourrepo/main/firmware.json"

#define CBL_GET_VER_CMD  0x10
#define ACK_BYTE         0xCD
#define NACK_BYTE        0xAB

const char* ssid = "YourWiFiName";
const char* password = "YourWiFiPassword";

HardwareSerial STM32Serial(1); // UART1 (RX=16, TX=17)

void setup() {
  Serial.begin(115200);
  STM32Serial.begin(115200, SERIAL_8N1, 16, 17);

  connectToWiFi();
  delay(1000);

  checkFirmwareUpdate();
}

void loop() {
  // Nothing here
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ WiFi Connected.");
  Serial.print("IP: "); Serial.println(WiFi.localIP());
}

void checkFirmwareUpdate() {
  HTTPClient http;
  http.begin(JSON_URL);
  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();
    Serial.println("📥 JSON received:");
    Serial.println(payload);

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      Serial.println("❌ Failed to parse JSON");
      return;
    }

    String newVersion = doc["version"];
    String fwUrl = doc["url"];
    String token = doc["token"];

    if (token != EXPECTED_TOKEN) {
      Serial.println("❌ Invalid token! Update rejected.");
      return;
    }

    if (newVersion != CURRENT_FIRMWARE_VERSION) {
      Serial.printf("🔄 New Version Available: %s\n", newVersion.c_str());
      Serial.println("📤 Sending command to STM32...");
      sendGetVersionCommand(); // Example bootloader interaction

      // لو عاوزه تحملي وتخزني fw هنا كمكمل للتحديث اكتبيلي وهكمله

    } else {
      Serial.println("✅ Already up to date.");
    }
  } else {
    Serial.print("❌ HTTP Error: ");
    Serial.println(httpCode);
  }

  http.end();
}

void sendGetVersionCommand() {
  uint8_t cmdPacket[6];
  uint32_t crc = calculateCRC((uint8_t*)&CBL_GET_VER_CMD, 1);
  cmdPacket[0] = 0x05;
  cmdPacket[1] = CBL_GET_VER_CMD;
  cmdPacket[2] = (crc >> 24) & 0xFF;
  cmdPacket[3] = (crc >> 16) & 0xFF;
  cmdPacket[4] = (crc >> 8) & 0xFF;
  cmdPacket[5] = crc & 0xFF;

  STM32Serial.write(cmdPacket, 6);
  delay(100);

  if (STM32Serial.available() >= 2) {
    uint8_t ack[2];
    STM32Serial.readBytes(ack, 2);
    if (ack[0] == ACK_BYTE) {
      uint8_t len = ack[1];
      uint8_t data[10];
      STM32Serial.readBytes(data, len);
      Serial.printf("✅ Bootloader version: %d.%d.%d (Vendor: %d)\n", data[1], data[2], data[3], data[0]);
    } else {
      Serial.println("❌ NACK or unknown response");
    }
  } else {
    Serial.println("❌ No response from STM32");
  }
}

uint32_t calculateCRC(const uint8_t *data, size_t len) {
  uint32_t crc = 0xFFFFFFFF;
  for (size_t i = 0; i < len; i++) {
    crc ^= ((uint32_t)data[i] << 24);
    for (int j = 0; j < 8; j++) {
      if (crc & 0x80000000)
        crc = (crc << 1) ^ 0x04C11DB7;
      else
        crc <<= 1;
    }
  }
  return crc;
}
