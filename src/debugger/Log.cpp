#include "Log.h"

String Log::_serverUrl;
String Log::_port;
DynamicJsonDocument Log::stateData(1024);
bool Log::enableLogging = false;

void Log::begin(
    const String wifiSSID, 
    const String wifiPassword, 
    const String serverUrl, 
    const String port) {
    _serverUrl = serverUrl;
    _port = port;

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
    serializeJson(stateData, jsonPayload);
    sendToServer(jsonPayload);
};

void Log::propertyChanged(String className, String propertyName, String newValue) {
    if (!enableLogging) return;
    stateData[className]["properties"][propertyName] = newValue;
};

void Log::d(String className, String message, String data) {
    if (!enableLogging) return;

    String jsonPayload;
    StaticJsonDocument<200> payload;

    payload["event"] = "message";
    payload["class"] = className;
    payload["message"] = message;
    payload["value"] = data;
    payload["ip"] = WiFi.localIP().toString();

    serializeJson(payload, jsonPayload);
    sendToServer(jsonPayload);
}

void Log::sendToServer(const String jsonData) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(_serverUrl + ":" + _port + "/api/broadcast");

        // Set headers
        http.addHeader("Content-Type", "application/json");

        // Send POST request
        int httpResponseCode = http.POST(jsonData);

        http.end(); // Free resources
    } else {
        // welp
    }
};