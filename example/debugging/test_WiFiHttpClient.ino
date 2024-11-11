#include <WiFiHttpClient.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Define the server URL and route (example: "http://your-server.com/api/route")
const char* serverUrl = "http://your-server.com/api/route";

// Create an instance of WiFiHttpClient
WiFiHttpClient client(ssid, password, serverUrl);

void setup() {
  // Initialize the Wi-Fi connection and HTTP client
  client.connectToWiFi();
}

void loop() {
  // Check if the Wi-Fi connection is still active
  client.checkWiFiConnection();
  
  // Send JSON data to the server every 10 seconds
  client.sendData("{\"temperature\": 25, \"humidity\": 50}");

  // Wait for 10 seconds before sending the next data
  delay(10000);
}
