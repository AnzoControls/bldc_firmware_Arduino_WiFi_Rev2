/*
 * AUTHOR : ANZO Controls Pvt Ltd
 *
 * This document is strictly confidential communication to and solely for the use
 * of the recipient and may not be reproduced or circulated without Anzo Controls's
 * Private Limited's prior written consent. If you are not the intended recipient,
 * you should not disclose or use the information in this document in any way.
 * The information is not intended as an offer or solicitation with respect to the
 * usage of this code.
 *
 * Strict legal proceeding would happen in case anyone has been found in violation
 * of the notice as above.
 */

#pragma once
#ifndef Mqtt_Header
#define Mqtt_Header 1

#include <iostream>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include "cust_libs/led.h"

class Mqtt {
  // Variables:
  std::string mqttServer;
  std::string mqttData;
  int mqttPort;
  int mqttTime;
  std::ofstream* logFile;
  char motorCommand;

  public:
  Led* led;
  // WiFiClient wifiClient;
  // PubSubClient mqttClient;
  // Methods of class
  void processData(char*, byte*, unsigned int);
  void setupMqttClient();
  void tryReconnectToBroker();
  void publishDataToBroker();
  void myLoop();

  // Setters
  void setMqttServerAddress(std::string iServer);
  void setMqttPortAddress(int iPort);
  void setMqttData(std::string iData);
  void setMqttTime(long iTime);
  void setLogFile(std::ofstream* filePtr);
  void setMotorCommand(char iMotorCommand);

  // Getters
  std::string getMqttServerAddress();
  std::string getMqttData();
  int getMqttPortAddress();
  long getMqttTime();
  std::ofstream* getLogFile();
  char getMotorCommand();

  // Ctor/Dtor
  Mqtt();
  ~Mqtt();
};

#endif
