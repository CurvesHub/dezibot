#ifndef WiFiHttpClient_h
#define WiFiHttpClient_h

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class WiFiHttpClient {
  private:
    const char* ssid;
    const char* password;
    const char* serverUrl;
    HTTPClient httpClient;

  public:
    // Constructor to connectToWiFi Wi-Fi credentials and server URL
    WiFiHttpClient(const char* ssid, const char* password, const char* serverUrl);

    // Method to establish a Wi-Fi connection
    void connectToWiFi();

    // Method to handle Wi-Fi reconnection
    void checkWiFiConnection();

    // Method to send JSON data to the server
    void sendData(const char* jsonData);
};

#endif
