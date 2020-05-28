#include <Arduino.h>
#include "Config.h"
#include "WiFi101.h"
#include "PubSubClient.h"

int status = WL_IDLE_STATUS;
WiFiClient wificlient;
PubSubClient mqttclient(wificlient);

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("siła sygnału (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void reconnect() {
  while (!mqttclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqttclient.connect("ArduinoMKR1000")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttclient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Łączenie się do SSID: ");
    Serial.println(config::m_eth_ssid);
    status = WiFi.begin(config::m_eth_ssid, config::m_eth_pass);
    delay(10000);
  }
  printWiFiStatus();
  mqttclient.setServer(config::m_mqtt_server_ip, 1883);

  pinMode(config::m_pin_sup_sens_res, OUTPUT);
}

void loop() 
{
  digitalWrite(config::m_pin_sup_sens_res, HIGH);
  delay(100);
  int measurement_sensor_1 = map(analogRead(config::m_pin_sens_res), 0, 1023, 0, 100);
  int measurement_sensor_2 = map(analogRead(config::m_pin_sens_cap_hor), 0, 1023, 0, 100);
  int measurement_sensor_3 = map(analogRead(config::m_pin_sens_cap_per), 0, 1023, 0, 100);
  int measurement_sensor_4 = map(analogRead(config::m_pin_sens_cap_per_hous), 0, 1023, 0, 100);

  Serial.println(measurement_sensor_1);
  Serial.println(measurement_sensor_2);
  Serial.println(measurement_sensor_3);
  Serial.println(measurement_sensor_4);

  if (!mqttclient.connected()) {
    reconnect();
  }

  char buf[4];
  sprintf(buf, "%05d", measurement_sensor_1);
  mqttclient.publish(config::m_mqtt_pub_topic_sens_1, buf);
  sprintf(buf, "%05d", measurement_sensor_2);
  mqttclient.publish(config::m_mqtt_pub_topic_sens_2, buf);
  sprintf(buf, "%05d", measurement_sensor_3);
  mqttclient.publish(config::m_mqtt_pub_topic_sens_3, buf);
  sprintf(buf, "%05d", measurement_sensor_4);
  mqttclient.publish(config::m_mqtt_pub_topic_sens_4, buf);

  digitalWrite(config::m_pin_sup_sens_res, LOW);
  delay(config::m_rep_time);
}