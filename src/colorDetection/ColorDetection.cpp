#include  "ColorDetection.h"
#include "../log/Log.h"


void ColorDetection::beginAutoMode(void) {
    const VEML_CONFIG DEFAULT_CONFIG = VEML_CONFIG {
        .mode = AUTO,
        .enabled = true,
        .exposureTime = MS320 };
    ColorDetection::configure(DEFAULT_CONFIG);
    Log::d(INFO, COLOR_DETECT_COMP, "configured color detection auto mode");
};

void ColorDetection::configure(VEML_CONFIG config) {
    rgbwSensor.begin();

    uint8_t configuration = 0;

    switch(config.exposureTime) {
        case MS40:
            configuration += VEML6040_IT_40MS;
            break;
        case MS80:
            configuration += VEML6040_IT_80MS;
            break;
        case MS160:
            configuration += VEML6040_IT_160MS;
            break;
        case MS320:
            configuration += VEML6040_IT_320MS;
            break;
        case MS640:
            configuration += VEML6040_IT_640MS;
            break;
        case MS1280:
            configuration += VEML6040_IT_1280MS;
            break;
    }

    configuration += (config.mode == MANUAL) ? VEML6040_AF_FORCE : VEML6040_AF_AUTO;
    configuration += config.enabled ? VEML6040_SD_ENABLE : VEML6040_SD_DISABLE;
    
    rgbwSensor.setConfiguration(configuration);
    Log::propertyChanged(COLOR_DETECT_COMP, "exposureTime", String(config.exposureTime));
    Log::propertyChanged(COLOR_DETECT_COMP, "enabled", String(config.enabled));
    Log::propertyChanged(COLOR_DETECT_COMP, "mode", String(config.mode));
    Log::d(INFO, COLOR_DETECT_COMP, "rgb sensor configured", String(configuration));
};

uint16_t ColorDetection::getColorValue(color color){
    uint16_t result;
    switch(color) {
        case VEML_RED:
            result = rgbwSensor.getRed();
        case VEML_GREEN:
            result = rgbwSensor.getGreen();
        case VEML_BLUE: 
            result = rgbwSensor.getBlue();
        case VEML_WHITE:
            result = rgbwSensor.getWhite();
        default:
            Serial.println("Color is not supported by the sensor");
            return 0;
    }
    Log::propertyChanged(COLOR_DETECT_COMP, "colorType" + String(color), String(result));
    return result;
};

float ColorDetection::getAmbientLight() {
    float result = rgbwSensor.getAmbientLight();
    Log::propertyChanged(COLOR_DETECT_COMP, "ambientLight", String(result));
    return result;
};
