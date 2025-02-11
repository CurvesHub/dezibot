#include "InfraredLight.h"
#include "../log/Log.h"

#define pwmSpeedMode LEDC_LOW_SPEED_MODE

InfraredLED::InfraredLED(uint8_t pin,ledc_timer_t timer, ledc_channel_t channel){
    this->ledPin = pin;
    this->timer = timer;
    this->channel = channel;
    Log::propertyChanged(INFRARED_COMP, "ledPin", String(this->ledPin));
    Log::propertyChanged(INFRARED_COMP, "timer", String(this->timer));
    Log::propertyChanged(INFRARED_COMP, "channel", String(this->channel));
};

void InfraredLED::begin(void){
   //we want to change frequency instead of 
    pwmTimer = ledc_timer_config_t{
        .speed_mode = pwmSpeedMode,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = this->timer,
        .freq_hz = 800,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&pwmTimer);
    Log::d(INFOLOG, INFRARED_COMP, "pwmTimer configured", String(this->timer));

    pwmChannel = ledc_channel_config_t{
        .gpio_num = this->ledPin,
        .speed_mode =pwmSpeedMode,
        .channel = this->channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = this->timer,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&pwmChannel);
    Log::d(INFOLOG, INFRARED_COMP, "channel configured", String(this->channel));
};

void InfraredLED::turnOn(void){
    InfraredLED::setState(true);
};

void InfraredLED::turnOff(void){
    InfraredLED::setState(false);
};

void InfraredLED::setState(bool state){
    ledc_set_freq(pwmSpeedMode,timer,1);
    if (state) {
        ledc_set_duty(pwmSpeedMode,channel,1023);
    } else {
        ledc_set_duty(pwmSpeedMode,channel,0);
    }
    ledc_update_duty(pwmSpeedMode,channel);
    
    Log::propertyChanged(INFRARED_COMP, "state", String(state));
};

void InfraredLED::sendFrequency(uint16_t frequency){
    ledc_set_freq(pwmSpeedMode,timer,frequency);
    ledc_set_duty(pwmSpeedMode,channel,512);
    ledc_update_duty(pwmSpeedMode,channel);
    Log::propertyChanged(INFRARED_COMP, "frequency", String(frequency));
};