#include <Dezibot.h>

const char* ssid = "ssid"; // your wifi name
const char* password = "pw"; // your wifi password

Dezibot dezibot;

void setup() {
  Serial.begin(115200);
  dezibot.begin();
  Log::begin(ssid, password, "http://your-ip-here" , "your-port-here");
}

void loop() {
  dezibot.display.print("Hello from\nDezibot");
  Log::update();
  delay(1000);
  dezibot.display.clear();
  Log::update();
  delay(1000);
  dezibot.lightDetection.getValue(DL_FRONT);
  dezibot.lightDetection.getAverageValue(IR_FRONT,20,1);
  dezibot.lightDetection.getBrightest(IR);
  Log::update()
  delay(1000);
}

