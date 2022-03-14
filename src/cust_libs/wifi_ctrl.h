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

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <fstream>

#pragma once
#ifndef Wifi_header
#define Wifi_header 1

class Wifi {
  std::string wifiName;
  std::string wifiPass;
  std::ofstream* logFile;
  public:
    void connectToWiFi();

    // Setters
    void setWifiName(std::string);
    void setWifiPass(std::string);
    void setLogFile(std::ofstream*);

    // Getters
    std::string getWifiName();
    std::string getWifiPass();
    std::ofstream* getLogFile();

    Wifi();
    ~Wifi();
};

#endif
