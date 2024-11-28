#include "Log.h"

String Log::_serverUrl;
DynamicJsonDocument Log::stateData(1024);
bool Log::enableLogging = false;

void Log::begin(
    const String wifiSSID, 
    const String wifiPassword, 
    const String serverUrl
    ) {
    _serverUrl = serverUrl;

    WiFi.begin(wifiSSID, wifiPassword);
    WiFi.setAutoReconnect(true);
    uint8_t retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
        retryCount++;
    }
    if (WiFi.status() == WL_CONNECTED) {
        enableLogging = true;
        stateData["event"] = "stateUpdated";
        stateData["ip"] = WiFi.localIP().toString();
        Serial.println("Connected to WiFi for logging!");
    }
};

void Log::update() {
    if (!enableLogging) return;

    String jsonPayload;
    stateData["ip"] = WiFi.localIP().toString();
    serializeJson(stateData, jsonPayload);
    sendToServer(jsonPayload);
};

void Log::propertyChanged(String className, String propertyName, String newValue) {
    if (!enableLogging) return;
    stateData["data"][className][propertyName] = newValue;
};

void Log::d(String className, String message, String data) {
    if (!enableLogging) return;

    StaticJsonDocument<200> payload;

    payload["ip"] = WiFi.localIP().toString();
    payload["className"] = className;
    payload["message"] = message;
    payload["data"] = data;

    String jsonPayload;
    serializeJson(payload, jsonPayload);
    sendToServer(jsonPayload);
}

void Log::sendToServer(const String jsonData) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(_serverUrl);

        // Set headers
        http.addHeader("Content-Type", "application/json");

        // Send POST request
        int httpResponseCode = http.PUT(jsonData);

        http.end(); // Free resources
    } else {
        Serial.println("Error: WiFi not connected.");
    }
};