#include <Dezibot.h>
#include <../src/log/Log.h>


const char* ssid = "ssid"; // your wifi name
const char* password = "pw"; // your wifi password

Dezibot dezibot = Dezibot();

void setup() {
  Serial.begin(115200);
  dezibot.begin();
  // TODO: Figure out how to use local ip to connet or deploy the service to azure for free
  Log::begin(ssid, password, "http://localhost:5160/api/dezibot/update");
}

void loop() {
  Log::update();
  delay(1000);

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
