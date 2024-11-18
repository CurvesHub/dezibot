#include "Logger.h"

// Initialize the static WiFiHttpClient pointer
WiFiHttpClient* Logger::client = nullptr;

// Static method to set the WiFiHttpClient instance
void Logger::setClient(WiFiHttpClient* newClient) { // TODO: Pass the creditentials to the constructor and new up the client here
  client = newClient;
}

// Convert the log level enum to a string
const char* Logger::logLevelToString(LogLevel level) {
  switch (level) {
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case ERROR:
      return "ERROR";
    case DEBUG:
      return "DEBUG";
    default:
      return "INFO"; // Default to INFO if the level is unknown
  }
}

// Private method to create a structured JSON document
String Logger::createLogJson(const char* message, LogLevel level) {
  // Dynamically allocate document size based on the message length
  size_t docSize = 1024 + strlen(message);
  DynamicJsonDocument doc(docSize);

  unsigned long timestamp = millis();
  doc["timestamp"] = timestamp;
  doc["level"] = logLevelToString(level);
  doc["message"] = message;

  String output;
  serializeJson(doc, output);
  return output;
}

// Static method to log a message
void Logger::log(const char* message, const char* level = "INFO") {
  if (client == nullptr) {
    Serial.println("Logger client not set!");
    return;
  }

  String jsonData = createLogJson(message, level);
  client->sendData(jsonData.c_str());
}
