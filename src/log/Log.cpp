#include "Log.h"

String Log::_url;
DynamicJsonDocument Log::stateData(1024);
bool Log::ENABLE_LOGGING = false;
HTTPClient Log::httpClient;

void Log::begin(const char* wifiSSID, const char* wifiPassword, String url) {
    _url = url;
    
    WiFi.begin(wifiSSID, wifiPassword);
    WiFi.setAutoReconnect(true);

    uint8_t retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        retryCount++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        ENABLE_LOGGING = true;
        stateData["ip"] = WiFi.localIP().toString();
        Serial.println("Connected to WiFi for logging!");
        httpClient.begin(_url);
    } else {
        Serial.println("Failed to connect to WiFi.");
    }
};

void Log::propertyChanged(String className, String propertyName, String newValue) {
    if (!ENABLE_LOGGING) return;
    stateData["data"][className][propertyName] = newValue;
};

void Log::d(String className, String message, String data) {
    if (!ENABLE_LOGGING) return;

    StaticJsonDocument<200> payload;

    payload["ip"] = WiFi.localIP().toString();
    payload["className"] = className;
    payload["message"] = message;
    payload["data"] = data;

    String jsonPayload;
    serializeJson(payload, jsonPayload);
    sendToServer(jsonPayload);
}

void Log::update() {
    if (!ENABLE_LOGGING) return;
    String jsonPayload;
    serializeJson(stateData, jsonPayload);
    sendToServer(jsonPayload);
};

void Log::sendToServer(String jsonData) {
    if (WiFi.status() == WL_CONNECTED) {
        httpClient.addHeader("Content-Type", "application/json");

        int responseCode = httpClient.PUT(jsonData);

        if (responseCode != 204) {
            Serial.printf("Received status code: %d\nResponse body:", responseCode);
            Serial.println(httpClient.getString());
        }
    } else {
        Serial.println("Error: WiFi not connected.");
    }
};