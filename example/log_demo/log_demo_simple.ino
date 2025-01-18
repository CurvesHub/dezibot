#include <Dezibot.h>
#include <../src/log/Log.h>

const char* ssid = "hotspot"; // your wifi name
const char* password = "password"; // your wifi password
const char* ipAdress = ""; // the ip adress of the backend server

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(115200);
    // You need to configure the Log first, to transmit the setup logs/data of dezibot components
    Log::begin(ssid, password, "http://" + ipAdress + ":5160/api/dezibot/update");
    dezibot.begin();
}

void loop() {
    dezibot.display.print("Hello World");
    delay(1000);
    dezibot.display.clear();

    // Sent data to server and use a deplay to reduce verbosity
    Log::update();
    delay(3000);
}
