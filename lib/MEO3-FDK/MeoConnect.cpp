#include "MeoConnect.h"

#include <WiFi.h>
#include <PubSubClient.h>

MeoConnect::MeoConnect() {}

void MeoConnect::setWifiConfig(char *ssid, char *wifiPassword) {
  this->ssid = ssid;
  this->wifiPassword = wifiPassword;
}

void MeoConnect::setMqttConfig(char *mqttServer, int mqttPort) {
  this->mqttServer = mqttServer;
  this->mqttPort = mqttPort;
}

void MeoConnect::initConfig() {
  WiFi.begin(this->ssid, this->wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");  
  }

  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.println("IP address: " + WiFi.localIP().toString());

  client.setServer(this->mqttServer, this->mqttPort);
}

void MeoConnect::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection");
    if (client.connect("MEO-3")) {
      Serial.println("\nConnected to MQTT Broker");
      client.publish("meo3/test", "Hello world from Arduino - MEO!");
    } else {
      Serial.print(".");
      delay(3000);
    }
  }
}

void MeoConnect::pubMessageToTopic(char *message, char *topic) {
  client.publish(topic, message, 1);
  client.flush();
}