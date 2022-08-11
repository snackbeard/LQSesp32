#include "hibernation.h"

void callback() {};

void Hibernation::enableTouchWakeup()
{
    touchAttachInterrupt(T3, callback, 40);
    esp_sleep_enable_touchpad_wakeup();
}

void Hibernation::startHibernation(uint32_t seconds)
{
    if (seconds > 0)
    {
        esp_sleep_enable_timer_wakeup(seconds * 1000000);
    }
    esp_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
    // esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF); // needed to be on for wakeup reason
    esp_deep_sleep_start();
}

uint8_t Hibernation::getWakeupReason()
{
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    switch (wakeup_reason)
    {
        case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); return 1;
        default: return 0;
    }
}