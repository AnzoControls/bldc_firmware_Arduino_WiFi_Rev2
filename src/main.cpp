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

#include <iostream>
#include <fstream>
#include "cust_libs/headers.h"
#include "cust_libs/mqtt.h"
#include "cust_libs/led.h"
#include "cust_libs/wifi_ctrl.h"

/****************************************************************************************************************/
#include "TLE9879_Group.h"

// Declare Shield group object
TLE9879_Group *shields;
int motorSpeed = 200;
int step = 100;



/****************************************************************************************************************/
// Creation of the wifi/mqtt objects
Wifi* wifi = new Wifi();
Mqtt* mqtt = new Mqtt();

// This function 'setup' gets called only once i.e. It initializes the things.
// We can write code which would get executed only once here.
void setup() {
  delay(5000);
  Serial.flush();
  // Setting up the serial baud rate
  Serial.begin(BAUD_RATE);

  // Starting an log file to keep the track
  // std::ofstream* logFile = new std::ofstream();
  // logFile->open(LOG_FILE_NAME, std::ios::out | std::ofstream::app);
  // if(!logFile->is_open()) {
  //   Serial.println("ERROR: FILE NOT OPENED.");
  // }

  // Setting up the member variables for both wifi/mqtt class
  // Reason why we don't have one common filePtr is because we probably
  // do not understand the Arduino infrastructure very well.
  // Ideally, there should be only one filePtr which is shareable across
  // all classes of this project.
  // wifi->setLogFile(logFile);
  // mqtt->setLogFile(logFile);

  // Defines the directions of the pins specified
  pinMode(mqtt->led->getSensorPin(), INPUT);
  // *logFile << "Pin number " << mqtt->led->getSensorPin() <<
  //          " made as sensor input" << std::endl;
  pinMode(mqtt->led->getLedPin(), OUTPUT);
  // *logFile << "Pin number " << mqtt->led->getLedPin() <<
  //          " made as led input" << std::endl;

  // Connects the esp32 board with the wifi
  // TODO: Collect the return status of this and take action accordingly.
  Serial.println("Connecting with WIFi");
  wifi->connectToWiFi();

  Serial.println("Setting up the mqtt clients");
  // Setting up the variables for making the esp32 board as an subscriber
  // TODO: Collect the return status of this and take action accordingly.
  mqtt->setupMqttClient();

  // Connect the client to the broker
  // Internally, it keeps trying till the time mqttClient is not connected
  // to the broker
  // mqtt->tryReconnectToBroker();
  


  /******************************************************************************************************************/
  // Initialize the Shield group object with the
  // number of Shields in the stack
  shields = new TLE9879_Group(1);
   
  // Set the desired mode (FOC, HALL, BEMF)
  shields->setMode(FOC);
  /******************************************************************************************************************/
}


void loop() {
  mqtt->myLoop();
  // Publish the data to broker
  mqtt->publishDataToBroker();
  
  shields->setMotorSpeed(motorSpeed);
  // start_motor();
  shields->setMotorMode(START_MOTOR);
  shields->setMotorMode(mqtt->getMotorCommand());
  delay(1000);
    
}
