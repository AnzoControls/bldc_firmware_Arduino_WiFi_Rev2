/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// Include the Shield library to your Arduino project
//#include "/home/ashraful/Arduino/libraries/TLE9879-BLDC-Shield-master/src/TLE9879_Group.h"
//#include "/home/ashraful/office_work/motor_Drive/bldc/BLED_Motor/lib/TLE9879-BLDC-Shield-master/src/TLE9879_Group.h"
/* #include<WiFiNINA.h>
#include <WiFi.h> */

/* 
* WiFi Configuration files
 */
/* 
const char* SSID = "OfficeBay";
const char* PASS = "Aarone@123";
int keyIndex = 0; */
/***************************************************************************************************/



#include "TLE9879_Group.h"
/* #include <iostream> */

// Declare Shield group object
TLE9879_Group *shields;
int motorSpeed = 100;


void setup()
{
  Serial.begin(9600);

/****************************************************************************/
/*   WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) 
  { 
    // Wait for the Wi-Fi to connect
    delay(500);
    Serial.print('.');
  }
  Serial.println(WiFi.localIP()); */

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
  delay(1000);
  motorSpeed += 50;
/*   Serial.println("Printing IP Address: ");
  Serial.println(WiFi.localIP()); */
}