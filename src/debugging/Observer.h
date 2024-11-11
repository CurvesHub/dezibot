#ifndef OBSERVER_H
#define OBSERVER_H

#include <WiFiHttpClient.h>
#include <ArduinoJson.h>
#include "Observable.h"

class Observer {
  private:
    WiFiHttpClient* client;
    Observable** observables;
    int observableCount;
    unsigned long lastUpdate;
    unsigned long updateInterval;

    // Private method to create a structured JSON document for the states
    String createStateJson() const;

  public:
    Observer(WiFiHttpClient* client, Observable** observables, int observableCount, unsigned long updateInterval = 10000);

    // Method to periodically update and send the state of all observables
    void update();

    // Change the update interval dynamically
    void setUpdateInterval(unsigned long newInterval);
};

#endif // OBSERVER_H
