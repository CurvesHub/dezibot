#include <Dezibot.h>
#include <../src/log/Log.h>


const char* ssid = "ssid"; // your wifi name
const char* password = "pw"; // your wifi password

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(115200);
    // It its importent to setup the log before the dezibot to transmit the setup logs
    Log::begin(ssid, password, "http://localhost:5160/api/dezibot/update");
    dezibot.begin();
}

void loop() {
    // TODO: Add exmaples for every component
    Log::update();
    delay(1000);

    Log::d(DEBUG, MAIN_PROGRAM, "Debug log from main");
    Log::d(INFO, MAIN_PROGRAM, "Info log from main");
    Log::d(WARN, MAIN_PROGRAM, "Warnings log from main");
    Log::d(ERROR, MAIN_PROGRAM, "Error log from main");

    dezibot.display.print("Hello from\nDezibot");
    Log::update();
    delay(1000);

    dezibot.display.clear();
    Log::update();
    delay(1000);

    dezibot.lightDetection.getValue(DL_FRONT);
    dezibot.lightDetection.getAverageValue(IR_FRONT,20,1);
    dezibot.lightDetection.getBrightest(IR);
    Log::update();
    delay(1000);
}
