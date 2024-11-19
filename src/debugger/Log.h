/**
 * @file Log.h
 * @author Tom Sosedow
 * @brief Adds the ability to debug and log
 * @version 0.1
 * @date 2024-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef Log_h
#define Log_h
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <map>

class Log {
    private:
        static String _serverUrl;
        static String _port;
        static DynamicJsonDocument stateData;
        static bool enableLogging;

    public:
        static void begin(
            const String wifiSSID, 
            const String wifiPassword, 
            const String serverUrl, 
            const String port
        );
        
        static void propertyChanged(String className, String propertyName, String newValue);
        static void d(String className, String message, String data);
        static void update();

        static void sendToServer(const String jsonData);

};

// used to map the components in the backend
const String DISPLAY_COMP = "DISPLAY";
const String RGB_SENSOR_COMP = "RGB_SENSOR";
const String INFRARED_COMP = "INFRARED";
const String LIGHT_DETECT_COMP = "LIGHT_DETECT";

#endif