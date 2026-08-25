#include <WiFi.h>
#include <Firebase_ESP_Client.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Your_Wifi_SSID"
#define WIFI_PASSWORD "Your_Wifi_Password"

/* 2. Define the Firebase API Key */
#define API_KEY "Your_Firebase_API_Key"

/* 3. Define the user Email and password */
#define USER_EMAIL "Your_Firebase_Email"
#define USER_PASSWORD "Your_Firebase_Password"

/* 4. Define the Firebase storage bucket ID */
#define STORAGE_BUCKET_ID "Your_Storage_Bucket_ID"

// Define a simple update command for STM32
#define UPDATE_COMMAND "START_UPDATE"

// Define the pin connected to the STM32
#define STM32_RX_PIN 16 // مثال، ممكن تغيريه حسب توصيلتك

// Global Variables
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
float currentVersion = 1.0; // رقم الإصدار الحالي للكود اللي على الـ STM32

// Forward declarations
void downloadCallback(FCS_DownloadStatusInfo info);
void sendFirmwareToSTM32(const char* filePath);

void setup() {
    Serial.begin(115200);
    // إعداد الـ UART لإرسال البيانات للـ STM32
    Serial2.begin(115200, SERIAL_8N1, -1, STM32_RX_PIN);
    Serial.println();
    
    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Configure Firebase
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    Firebase.reconnectNetwork(true);
    Firebase.begin(&config, &auth);
}

void loop() {
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 5000 || sendDataPrevMillis == 0)) {
        sendDataPrevMillis = millis();

        float latestVersion;
        // قراءة رقم الإصدار من قاعدة البيانات
        if (Firebase.RTDB.getDouble(&fbdo, "/firmware/version", &latestVersion)) {
            Serial.printf("Current Version: %.1f, Latest Version: %.1f\n", currentVersion, latestVersion);
            
            // لو فيه تحديث جديد
            if (latestVersion > currentVersion) {
                Serial.println("New firmware available! Downloading...");
                
                // تحميل ملف التحديث من Storage
                if (!Firebase.Storage.download(&fbdo, STORAGE_BUCKET_ID, "/firmware.bin", "/firmware.bin", mem_storage_type_flash, downloadCallback)) {
                    Serial.println(fbdo.errorReason());
                }
            } else {
                Serial.println("Firmware is up-to-date.");
            }
        } else {
            Serial.println(fbdo.errorReason().c_str());
        }
    }
}

// دالة لمعالجة حالة التحميل
void downloadCallback(FCS_DownloadStatusInfo info) {
    if (info.status == firebase_fcs_download_status_download) {
        Serial.printf("Downloaded %d%s, Elapsed time %d ms\n", (int)info.progress, "%", info.elapsedTime);
    } else if (info.status == firebase_fcs_download_status_complete) {
        Serial.println("Download complete!");
        // بعد انتهاء التحميل، يتم استدعاء دالة الإرسال
        sendFirmwareToSTM32("/firmware.bin");
    }
}

// دالة لإرسال ملف التحديث للـ STM32
void sendFirmwareToSTM32(const char* filePath) {
    File firmwareFile = LittleFS.open(filePath, "r");
    if (!firmwareFile) {
        Serial.println("Failed to open firmware file for sending.");
        return;
    }

    // إرسال أمر البدء
    Serial.println("Sending update command to STM32...");
    Serial2.println(UPDATE_COMMAND);
    delay(100); // إعطاء وقت للـ STM32 ليكون جاهزًا

    // إرسال الملف بايت بايت
    Serial.println("Sending firmware file...");
    while(firmwareFile.available()){
        Serial2.write(firmwareFile.read());
    }

    firmwareFile.close();
    Serial.println("Firmware file sent successfully.");
}
