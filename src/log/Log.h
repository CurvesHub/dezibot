/**
 * @file Log.h
 * @author Tom Sosedow, Jens Richter
 * @brief Adds the ability to log events and state changes to a web server.
 * @version 0.3
 * @date 2024-11-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef Log_h
#define Log_h

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/** Log level enumeration for classifying log messages. */
enum LogLevel { 
    DEBUG,
    INFO,
    WARN,
    ERROR
};

/** Class name constants for logging components. */
#define MAIN_PROGRAM "MAIN"
#define DISPLAY_COMP "DISPLAY"
#define RGB_SENSOR_COMP "RGB_SENSOR"
#define INFRARED_COMP "INFRARED"
#define LIGHT_DETECT_COMP "LIGHT_DETECT"
#define MOTION_DETECT_COMP "MOTION_DETECT"
#define COMMUNICATION_COMP "COMMUNICATION"
#define COLOR_DETECT_COMP "COLOR_DETECT"
#define MOTOR_COMP "MOTOR"
#define MOTION_COMP "MOTION"
#define RGB_LIGHT_COMP "MULTI_COLOR_LIGHT"

/**
 * @class Log
 * @brief Provides methods to log events and state changes to a web server over WiFi.
 */
class Log {
    private:
        static String _url;                       // The URL of the logging server.
        static DynamicJsonDocument stateData;     // Stores the current state data for periodic updates.
        static bool ENABLE_LOGGING;               // Flag indicating whether logging is enabled.
        static HTTPClient httpClient;             // HTTP client used for making requests.

        /**
         * @brief Converts the LogLevel enum to a string.
         * 
         * @param level The log level to convert.
         * @return A string representation of the log level.
         */
        static String logLevelToString(LogLevel level);

    public:
        /**
         * @brief Initializes the logging system by connecting to WiFi and setting up the server URL.
         * 
         * @param wifiSSID The SSID of the WiFi network to connect to.
         * @param wifiPassword The password for the WiFi network.
         * @param url The URL of the web server for logging data.
         */
        static void begin(const char* wifiSSID, const char* wifiPassword, String url);

        /**
         * @brief Logs a property change event for a given class and property.
         * 
         * @param className The name of the class where the property changed.
         * @param propertyName The name of the property that changed.
         * @param newValue The new value of the property.
         */
        static void propertyChanged(String className, String propertyName, String newValue);

        /**
         * @brief Logs a message with a specified log level and associated data payload.
         * 
         * @param level The log level of the message.
         * @param className The name of the class generating the message.
         * @param message A short message describing the event.
         * @param data Additional data to log (optional, defaults to an empty string).
         */
        static void d(LogLevel level, String className, String message, String data = "");

        /**
         * @brief Sends the current state data to the server.
         */
        static void update();
    
    protected:
        /**
         * @brief Sends a JSON payload to the logging server.
         * 
         * @param jsonData The JSON data to send.
         */
        static void sendToServer(String jsonData);
};

#endif //Log_h
