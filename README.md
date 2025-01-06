### Just esp32 playground

required to create a /src/secrets.h file containing
```
#define WIFI_SSID "wifi ssid"
#define WIFI_PASS "wifi password"
#define MQTT_SERVER "server ip"
#define MQTT_PORT 1883
#define MQTT_USERNAME "mqtt username"
#define MQTT_PASSWORD "mqtt password"
```

### Upload
- Build and upload code
- Upload filesystem

### TODO:
- [x] [HTTP server](https://randomnerdtutorials.com/esp32-web-server-arduino-ide/)
- [x] Mosquito queue client with sending led status to home assistant when led switched on/off (using HTTP server)
- [ ] plug in external LED
- [ ] plug in humidity sensor
- [ ] RGB LED?
- [ ] setup humidity + LED
- [ ] ?