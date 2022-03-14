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

#include "cust_libs/wifi_ctrl.h"
#include "cust_libs/headers.h"

/*
  Function      : Wifi
  Accepts       : Nothing. Constructor
  Returns       : None
  Abstraction   : Constructor
  Modified by   : 24th Feb, 2021 : Ashraful
 */
Wifi::Wifi() {
  setWifiName(WIFI_NAME);
  setWifiPass(WIFI_PASS);
}

/*
  Function      : Wifi
  Accepts       : Nothing. Destructor
  Returns       : None
  Abstraction   : Destructor
  Modified by   : 24th Feb, 2021 : Ashraful
 */
Wifi::~Wifi() {
}

/*
  Function      : connectToWifi
  Accepts       : Nothing.
  Returns       : void
  Abstraction   : This function authenticate the wifi.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Wifi::connectToWiFi() {
  // *getLogFile() << "Wifi name : " << getWifiName() << std::endl;
  // *getLogFile() << "Wifi pass : " << getWifiPass() << std::endl;
  // *getLogFile() << "Connecting with the wifi ";
  Serial.println("Wifi name : " + String(getWifiName().c_str()));
  Serial.println("Wifi pass : " + String(getWifiPass().c_str()));
  Serial.println("Connecting with the wifi..");

  // Connecting to wifi
  WiFi.begin(getWifiName().c_str(), getWifiPass().c_str());

  // Keeps trying till the time it is not connected.
  // TODO: Again, we should not try indefinitely. If it can not be connected
  // in some time, we should break away.
  while (WiFi.status() != WL_CONNECTED) {
    // *getLogFile() << ".";
    Serial.print(".");
    delay(100);
  }

  // If connected, print the details
  if (WiFi.status() == WL_CONNECTED) {
    // *getLogFile() << "Board is connected to the wifi"   << std::endl;
    // *getLogFile() << "IP Address " << WiFi.localIP()    << std::endl;
    // *getLogFile() << "Subnet Mask" << WiFi.subnetMask() << std::endl;
    // *getLogFile() << "Gateway IP"  << WiFi.gatewayIP()  << std::endl;
    // *getLogFile() << "DNS"         << WiFi.dnsIP()      << std::endl;
    Serial.println("\nBoard is connected to the wifi");
    Serial.print("IP Address  : ");
    Serial.println(WiFi.localIP());
    Serial.print("Subnet Mask : ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway IP  : ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("DNS         : ");
    Serial.println(WiFi.dnsIP());
  }
} 

// Setters
/*
  Function      : setWifiName
  Accepts       : std::string.
  Returns       : void
  Abstraction   : This function sets the wifi name.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Wifi::setWifiName(std::string iWifiName) {
  wifiName = iWifiName;
}

/*
  Function      : setWifiPass
  Accepts       : std::string.
  Returns       : void
  Abstraction   : This function sets the wifi pass.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Wifi::setWifiPass(std::string iWifiPass) {
  wifiPass = iWifiPass;
}

/*
  Function      : setLogFile
  Accepts       : std::ofstream.
  Returns       : void
  Abstraction   : This function sets the wifi pass.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Wifi::setLogFile(std::ofstream* filePtr) {
  logFile = filePtr;
}

// Getters
/*
  Function      : getWifiName
  Accepts       : std::string.
  Returns       : void
  Abstraction   : This function returns the wifi name.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::string Wifi::getWifiName() {
  return wifiName;
}

/*
  Function      : getWifiPass
  Accepts       : None
  Returns       : std::string
  Abstraction   : This function returns the wifi pass.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::string Wifi::getWifiPass() {
  return wifiPass;
}

/*
  Function      : getLogFile
  Accepts       : None
  Returns       : ofstream&
  Abstraction   : This function returns the wifi pass.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::ofstream* Wifi::getLogFile() {
  return logFile;
}
