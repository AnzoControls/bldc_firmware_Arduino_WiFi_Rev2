/**
 * @file main.cpp
 * @author your name (ashraful-khan)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022 : GNU License
 * 
 */


/**
 * 
 * 
 * All wifi related configurationsd
 * 
 * /

/***************************************************************************************************/
#include <SPI.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

#include "arduino_secrets.h" 
int status = WL_IDLE_STATUS;


/***************************************************************************************************/


/**
 * Wifi Config ends
 * 
 * */

#include "TLE9879_Group.h"

// Declare Shield group object
TLE9879_Group *shields;
int motorSpeed = 200;
int step = 100;


char ssid[] = SECRET_SSID;    
char pass[] = SECRET_PASS; 

/*Print wifi status*/
/***************************************************************/
void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


void setup()
{
  Serial.begin(9600);

/****************************************************************************/
while (!Serial)
{
  ;
}

WiFiClient WiFiClient;
PubSubClient PubSubClient(WiFiClient);

if (WiFi.status()==WL_NO_MODULE){
  Serial.println("Communitcation with WiFi module is failed!!");
  while (true);
}


while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();


/****************************************************************************/
  // Initialize the Shield group object with the
  // number of Shields in the stack
  shields = new TLE9879_Group(1);
   
  // Set the desired mode (FOC, HALL, BEMF)
  shields->setMode(FOC);
}


void loop()
{
  shields->setMotorSpeed(motorSpeed);
  // start_motor();
  shields->setMotorMode(START_MOTOR);
  
  motorSpeed = motorSpeed + step;
  if (motorSpeed == 0 || motorSpeed == 600){
    step = -step;
  }
  delay(1000);
}