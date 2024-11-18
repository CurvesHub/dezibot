#include <WiFiHttpClient.h>
#include "Observer.h"
#include "Observable.h"

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverUrl = "http://your-server.com/api/route";

// Example Observable Class (e.g., for a Display)
class Display : public Observable {
public:
  bool flipped;
  int currentLine;

    DynamicJsonDocument state;
    String getPropertyState() const override {
        // Return the state as a JSON string
        DynamicJsonDocument doc(256);
        doc["className"] = "Display";
        doc["properties"]["currentLine"] = 16;
        doc["properties"]["orientation"] = "flipped";

        String state;
        serializeJson(doc, state);
        return state;
    }
    void someMethode() {
      int brightness = 100;
        // state json anpassen
      state["brightness"] = brightness;
    }
};

Display display; // Create an instance of Display

// Create an array of Observable pointers
Observable* observables[] = { &display };

// Create an instance of WiFiHttpClient
WiFiHttpClient client(ssid, password, serverUrl);

// Create an Observer instance
Observer observer(&client, observables, 1);

void setup() {
  Serial.begin(115200);
  client.connectToWiFi();
}

void loop() {
  observer.update();  // Periodically check and send the state of all observables
  
  // Optionally adjust the interval dynamically
  observer.setUpdateInterval(5000); // Change interval to 5 seconds
  
  delay(100);  // Small delay to prevent overloading the CPU
}
