#include <PubSubClient.h>
#include <WiFi.h>
#include "secrets.h"

const char *MQTT_TOPIC = "esp32/test";

WiFiClient espClient;
PubSubClient client(espClient);
String clientId = "";

void connectToMqtt() {
  client.setServer(MQTT_SERVER, MQTT_PORT);

  Serial.print("Connecting to MQTT...");

  while (!client.connected()) {
    clientId = "esp32-client-";
    clientId += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the MQTT broker\n", clientId.c_str());

    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void publishMessage(const char *message) {
  if (!client.connected()) {
    Serial.println("MQTT client not connected");
    connectToMqtt();
  }

  if (client.connected()) {
    Serial.println("Publishing message to MQTT topic");

    char msg[100];
    strcpy(msg, message);
    strcat(msg, ", from ");
    strcat(msg, clientId.c_str());

    client.publish(MQTT_TOPIC, msg);
  } else {
    Serial.println("MQTT client not connected");
  }
}
