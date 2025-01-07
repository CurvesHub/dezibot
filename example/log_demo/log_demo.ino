#include <Dezibot.h>
#include <../src/log/Log.h>


const char* ssid = "hotspot"; // your wifi name
const char* password = "password"; // your wifi password

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(115200);
    // It its importent to setup the log before the dezibot to transmit the setup logs
    Log::begin(ssid, password, "http://ipAdress:5160/api/dezibot/update");
    dezibot.begin();
}

void loop() {
    // TODO: Add exmaples for every component
    Log::update();
    delay(1000);

    Log::d(DEBUGLOG, MAIN_PROGRAM, "Debug log from main");
    Log::d(INFOLOG, MAIN_PROGRAM, "Info log from main");
    Log::d(WARNLOG, MAIN_PROGRAM, "Warnings log from main");
    Log::d(ERRORLOG, MAIN_PROGRAM, "Error log from main");

    dezibot.display.print("TEST: LogLevel");
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
