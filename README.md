# LQSesp32

ESP32 reads eCO2 and TVOC values from Sensirion SGP30 Multigas Sensor

- Using it for the first time, controller enters a setup phase for 24 hours (burn in time) and calculates a baseline value
- After the setup, it measures a value every 15 minutes and enters deepsleep mode afterwards (for minimal power consumption)
- GPIO PIN 15 (touch pin) on touch causes a wakeup -> bluetooth gets enabled and the controller can be configured with the android app
- SSID, Password, Server IP, Port & Controller Name can be configured
- if a new configuration is sent to the controller, it will enter setup mode again (assuming the user changed it's location, so the old baseline is incorrect)
