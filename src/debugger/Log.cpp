#include "Log.h"

String Log::_serverUrl;
String Log::_port;

void Log::begin(
    const String wifiSSID, 
    const String wifiPassword, 
    const String serverUrl, 
    const String port) {
    _serverUrl = serverUrl;
    _port = port;

    WiFi.begin(wifiSSID, wifiPassword);
    WiFi.setAutoReconnect(true);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi for logging!");
};

void Log::propertyChanged(String className, String propertyName, String newValue) {
    if (_serverUrl.length() == 0 || _port.length() == 0) {
        Serial.println("Logger not initialized! Use Log::begin to initialize the logging");
        return;
    }

    std::map<String, String> payload;
    payload["event"] = "propertyChanged";
    payload["class"] = className;
    payload["propName"] = propertyName;
    payload["value"] = newValue;
    payload["ip"] = WiFi.localIP().toString();


    sendToServer(payload);
};

void Log::d(String className, String message, String data) {
    if (_serverUrl.length() == 0 || _port.length() == 0) {
        Serial.println("Logger not initialized! Use Log::begin to initialize the logging");
        return;
    }

    std::map<String, String> payload;
    payload["event"] = "message";
    payload["class"] = className;
    payload["eventName"] = message;
    payload["value"] = data;
    payload["ip"] = WiFi.localIP().toString();


    sendToServer(payload);
}

void Log::sendToServer(const std::map<String, String> data) {
    String jsonPayload;
    StaticJsonDocument<200> jsonDoc;
    for (auto it = data.begin(); it != data.end(); ++it) {
        jsonDoc[it->first] = it->second;
    }
    serializeJson(jsonDoc, jsonPayload);

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        http.begin(_serverUrl + ":" + _port + "/api/broadcast");

        // Set headers
        http.addHeader("Content-Type", "application/json");

        // Send POST request
        int httpResponseCode = http.POST(jsonPayload);

        http.end(); // Free resources
    } else {
        // welp
    }
};