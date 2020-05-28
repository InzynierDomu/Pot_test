/*
 * Pins_config.h
 *
 *  Created on: Mar 24, 2019
 *      Author: inżynier Domu
 */

#ifndef CONFIG_H_
#define CONFIG_H_

namespace config
{
const int m_pin_sens_res = A1;
const int m_pin_sup_sens_res = 1;
const int m_pin_sens_cap_hor = A2;
const int m_pin_sens_cap_per = A3;
const int m_pin_sens_cap_per_hous = A4;

const int m_rep_time = 600000;

const String m_eth_ssid = "";
const String m_eth_pass = "";

const char* m_mqtt_server_ip = "192.168.0.150";   
const char* m_mqtt_pub_topic_sens_1 = "pot/sensor_1";   
const char* m_mqtt_pub_topic_sens_2 = "pot/sensor_2";   
const char* m_mqtt_pub_topic_sens_3 = "pot/sensor_3";   
const char* m_mqtt_pub_topic_sens_4 = "pot/sensor_4";   

}
#endif /* CONFIG_H_ */
