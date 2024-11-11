#include <WiFiHttpClient.h>
#include <Logger.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Define the server URL and route
const char* serverUrl = "http://your-server.com/api/log";

// Create an instance of WiFiHttpClient
WiFiHttpClient client(ssid, password, serverUrl);

// Set the WiFiHttpClient instance for the Logger
void setup() {
  Serial.begin(115200);
  client.connectToWiFi();
  Logger::setClient(&client);  // Set the WiFiHttpClient instance for Logger
}

void loop() {
  // Log various messages with different levels
  Logger::log("System initialized", INFO);
  Logger::log("Low disk space", WARNING);
  Logger::log("Error connecting to database", ERROR);
  Logger::log("Debugging mode activated", DEBUG);

  // Wait 10 seconds before logging again
  delay(10000);
}
