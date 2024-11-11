#ifndef Logger_h
#define Logger_h

#include <WiFiHttpClient.h>
#include <ArduinoJson.h>

enum LogLevel {
  INFO,
  WARNING,
  ERROR,
  DEBUG
};

class Logger {
  private:
    static WiFiHttpClient* client;
    static const char* logLevelToString(LogLevel level);
    static String createLogJson(const char* message, LogLevel level);

  public:
    // Static method to set the client
    static void setClient(WiFiHttpClient* newClient);

    // Static method to log the message
    static void log(const char* message, LogLevel level = INFO);
};

#endif
