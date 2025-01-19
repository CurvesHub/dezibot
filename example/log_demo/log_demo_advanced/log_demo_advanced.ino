#include <Dezibot.h>
#include <../src/log/Log.h>

const char* ssid = "hotspot"; // your wifi name
const char* password = "password"; // your wifi password
String ipAdress = ""; // the ip adress of the backend server

Dezibot dezibot = Dezibot();

void setup() {
    Serial.begin(115200);
    // You need to configure the Log first, to transmit the setup logs/data of dezibot components
    Log::begin(ssid, password, "http://" + ipAdress + ":5160/api/dezibot/update");
    dezibot.begin();
}

// This is an example of how to use the Log class
void loop() {
    // You can use the Log class to log data assosiated with a log level which is directly sent to the server
    Log::d(DEBUGLOG, MAIN_PROGRAM, "Debug log from main");
    Log::d(INFOLOG, MAIN_PROGRAM, "Info log from main");
    Log::d(WARNLOG, MAIN_PROGRAM, "Warnings log from main");
    Log::d(ERRORLOG, MAIN_PROGRAM, "Error log from main");

    // You can also log data from the components of the dezibot which are stored in the Log class
    Log::propertyChanged(MAIN_PROGRAM, "someProperty", "someValue");

    // You can call the update method to send stored components data to the server
    Log::update();

    // Calling some explample components to generate logs and state data

    // Display
    dezibot.display.print("Hello World");
    delay(1000);
    dezibot.display.clear();
    dezibot.display.flipOrientation();
    dezibot.display.invertColor();
    dezibot.display.print("Flipped and Inverted");
    delay(1000);
    dezibot.display.clear();
    dezibot.display.flipOrientation();
    dezibot.display.invertColor();

    // Light Detection
    dezibot.lightDetection.getValue(DL_FRONT);
    dezibot.lightDetection.getBrightest(IR);
    dezibot.lightDetection.getAverageValue(IR_FRONT,20,1);

    // Sent data to server and use a deplay to reduce verbosity
    Log::update();
    delay(3000);
}
