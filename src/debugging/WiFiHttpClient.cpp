#include "WiFiHttpClient.h"

// Constructor to connectToWiFi Wi-Fi credentials and server URL
WiFiHttpClient::WiFiHttpClient(const char* ssid, const char* password, const char* serverUrl) {
  this->ssid = ssid;
  this->password = password;
  this->serverUrl = serverUrl;
}

// Method to connectToWiFi Wi-Fi connection
void WiFiHttpClient::connectToWiFi() {
  Serial.println("Connecting to WiFi...");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 10) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.println("LocalIp: " + WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi after 10 attempts. Please check credentials.");
  }
}

// Method to handle Wi-Fi reconnection
bool WiFiHttpClient::checkWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Attempting to reconnect...");
    connectToWiFi();
  }

  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

// Method to send JSON data to the server
void WiFiHttpClient::sendData(const char* jsonData) {
  if (checkWiFiConnection()) {
    Serial.println("Sending JSON data:");
    Serial.println(jsonData);
    
    httpClient.begin(serverUrl);
    httpClient.addHeader("Content-Type", "application/json");
    httpClient.setTimeout(5000);

    int httpResponseCode = httpClient.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Server response:\n" + httpClient.getString());
    } else {
      Serial.print("Error in HTTP request: ");
      Serial.println(httpResponseCode);
    }

    httpClient.end();
  } else {
    Serial.println("Error: WiFi not connected.");
  }
}
