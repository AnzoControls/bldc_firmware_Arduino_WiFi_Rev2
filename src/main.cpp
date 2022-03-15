#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// Include the Shield library to your Arduino project
#include "TLE9879_Group.h"


// Declare Shield group object
TLE9879_Group *shields;

const char *SSID = "OfficeBay";
const char *PWD = "Aarone@123";

long last_time = 0;
char data[100];

int motorSpeed = 1000;
int step = 100;

//int senseor_pin = 27;
int led_pin = LED_BUILTIN;

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

char *mqttServer = "192.168.0.103";
int mqttPort = 1883;


void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("Connected.");
  
} 

char callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message Receieved: ");
  
    for (int i = 0; i < length; i++) {
      Serial.println(" ");
      Serial.println((char)payload[i]);
          
      //int m = ((char)payload[i]);
      int reading = ((char)payload[i]);
      //Serial.print("debug message1: ");
      //Serial.println(reading);
      Serial.print("Recieved Reading : ");
      Serial.println(reading);
      
      if (reading == 49){
         digitalWrite(led_pin, HIGH);
         shields->setMotorMode(START_MOTOR);
      }

      else if (reading == 48)
      {
        /* code */
         digitalWrite(led_pin, LOW);
         shields->setMotorMode(STOP_MOTOR);
      }
  
}
}

void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.print("Reconnecting to MQTT Broker..: ");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      Serial.println(clientId);

      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
             
        // subscribe to topic
        mqttClient.subscribe("motor1");
        delay(100);
      }
  }
}

void setup() {
  Serial.begin(9600);



  //pinMode(senseor_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  
  connectToWiFi();
  setupMQTT();

  	// Initialize the Shield group object with the
	// number of Shields in the stack
	shields = new TLE9879_Group(1);
	
	// Set the desired mode (FOC, HALL, BEMF)
	shields->setMode(FOC);
	
	// Set the desired motor speed (RPM)
	shields->setMotorSpeed(motorSpeed);
	


}
/* 
void publishing(){

  long now = millis();
  if (now - last_time > 500) {
      // Send data
      int sensed_data = digitalRead(senseor_pin);

      //Serial.println("**********************");

      // Publishing data throgh MQTT
      sprintf(data, "%d", sensed_data);
      Serial.printf("Published value: %s", data);
     // Serial.println("**********************");
      Serial.println(" ");

      mqttClient.publish("/swa/sensro_status", data);
      
      last_time = now;
   }
} */

void loop() {

  shields->setMotorSpeed(motorSpeed);

  if (!mqttClient.connected()) {
     reconnect();
  }
   mqttClient.loop();
   motorSpeed = motorSpeed + step;
  if (motorSpeed == 0 || motorSpeed == 2000){
    step = -step;
  }
  delay(1000);
}