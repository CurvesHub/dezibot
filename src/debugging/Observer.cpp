#include "Observer.h"

Observer::Observer(WiFiHttpClient* client, Observable** observables, int observableCount, unsigned long updateInterval = 1000) // TODO: Pass the creditentials to the constructor and new up the client here
  : client(client), observables(observables), observableCount(observableCount), updateInterval(updateInterval), lastUpdate(0) {}

// Method to create a structured JSON document for the states
String Observer::createStateJson() const {
  DynamicJsonDocument doc(1024); // Use a 1KB buffer for the JSON document
  JsonArray observablesArray = doc.createNestedArray("observables");

  for (int i = 0; i < observableCount; i++) {
    JsonObject observableObj = observablesArray.createNestedObject();
    observableObj["state"] = observables[i]->getPropertyState();
  }

  String output;
  serializeJson(doc, output);
  return output;
}

// Periodically update and send the state of all observables
void Observer::update() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastUpdate >= updateInterval) {
    String jsonData = createStateJson();
    
    if (client != nullptr && client->checkWiFiConnection()) {
        client->sendData(jsonData.c_str());
    } else {
        Serial.println("Error: WiFiHttpClient not initialized or no WiFi connection");
    }
    lastUpdate = currentMillis;
  }
}

// Dynamically update the update interval
void Observer::setUpdateInterval(unsigned long newInterval) {
    updateInterval = newInterval;
    Serial.print("Update interval set to: ");
    Serial.println(updateInterval);
}
