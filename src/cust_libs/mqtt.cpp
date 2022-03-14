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

#include <cstring>
#include "cust_libs/mqtt.h"
#include "cust_libs/wifi_ctrl.h"
#include "cust_libs/led.h"
#include "cust_libs/headers.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

/*
  Function      : mqtt
  Accepts       : Nothing. Constructor
  Returns       : None
  Abstraction   : Constructor
  Modified by   : 24th Feb, 2021 : Ashraful
 */
Mqtt::Mqtt() {
  setMqttServerAddress(SERVER_ADDRESS);
  setMqttPortAddress(SERVER_PORT);
  setMqttTime(0);
  led = new Led();
}

/*
  Function      : processData
  Accepts       : char*, byte*, unsigned int
  Returns       : char
  Abstraction   : This is an callback function which is called when subscriber
                  got the data as per the subscription.
  Modified by   : 24th Feb, 2021 : Ashraful
 *
*/
void Mqtt::processData(char* topic, byte* payload,
                 unsigned int length) {
  // Converting the payload to std::string so that we can compare
  std::string data = std::string((char*)(payload));

  // This just marks the termination of the char array.
  payload[length] = '\0';

  // Dumping the information into the log file
  // *getLogFile() << "Topic received    : " << topic   << std::endl;
  // *getLogFile() << "Message received  : " << payload << std::endl;
  // *getLogFile() << "Length of message : " << length  << std::endl;
  Serial.println("Topic received    : " + String(topic));
  Serial.println("Message received  : " + String((char*)(payload))); 
  Serial.println("Length of message : " + String(length)); 

  // Based on the message received from the broker, we either switch
  // OFF or switch ON the led of the board
  if((strcmp((char *)payload, "ON")) == 0) {
    digitalWrite(led->getLedPin(), HIGH);
    setMotorCommand("START_MOTOR");
  } else if ((strcmp((char *)payload, "OFF")) == 0) {
    digitalWrite(led->getLedPin(), LOW);
    setMotorCommand("STOP_MOTOR");
  }
}

/*
  Function      : setupMQTT
  Accepts       : Nothing.
  Returns       : void 
  Abstraction   : This configures the mqttClient specifications
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setupMqttClient() {
  // *getLogFile() << "Broker address : " << getMqttServerAddress() << std::endl;
  // *getLogFile() << "Port address   : " << getMqttPortAddress()   << std::endl;
  // Connecting the client with the broker 
/*
   *getLogFile() << "Setting up the boards's server configuration for \
connecting with the broker" << std::endl;
*/

  Serial.print("Broker address : ");
  Serial.println(String(getMqttServerAddress().c_str()));
  Serial.print("Port address   : ");
  Serial.println(getMqttPortAddress());
  Serial.println("Setting up the boards's server configuration for \
connecting with the broker");

  // Converting the std::string into char array since setServer
  // accepts only char[]. For some reason, it does not accept
  // char* which we can get using std::string.c_str()
  int arrSize = getMqttServerAddress().size();
  char charArray[arrSize + 1];
  strcpy(charArray, getMqttServerAddress().c_str());
  mqttClient.setServer(charArray, getMqttPortAddress());

  // Callback for receiving messages from broker
/*
  *getLogFile() << "Setting up the boards's callback function information for \
each message received by the subscriber" << std::endl;
*/
  Serial.println("Setting up the boards's callback function information for \
each message received by the subscriber");

  mqttClient.setCallback([this] (char* topic, byte* payload,
                                 unsigned int length) {
    this->processData (topic, payload, length);
  });

  // Converting the std::string into char array since setServer
  // accepts only char[]. For some reason, it does not accept
  // char* which we can get using std::string.c_str()
  arrSize = std::string(CLIENT_ID).size();
  char clientIDCharArray[arrSize];
  strcpy(clientIDCharArray, std::string(CLIENT_ID).c_str());

  // Appending the client ID to the string needs to be printed
  Serial.println("ClientID = " + String(clientIDCharArray));

  if (mqttClient.connect(clientIDCharArray)) {
    // *getLogFile() << "Connected the subscriber with the broker";
    Serial.println("Connected the subscriber with the broker");

    // Converting the std::string into char array since setServer
    // accepts only char[]. For some reason, it does not accept
    // char* which we can get using std::string.c_str()
    arrSize = std::string(TOPIC_NAME).size();
    char topicNameArray[arrSize + 1];
    strcpy(topicNameArray, std::string(TOPIC_NAME).c_str());

    // Subscribe to topic
    mqttClient.subscribe(topicNameArray);
    // *getLogFile() << "Subscriber subscribed to the topic " << TOPIC_NAME << std::endl;
    Serial.println("Subscriber subscribed to the topic" + String(topicNameArray));
  } else {
    Serial.println("Connection failed while connecting the subscriber \
with the broker.");
/*
    *getLogFile() << "Connection failed while connecting the subscriber \
with the broker." << std::endl;
*/
  }
}

/*
  Function      : tryReconnectToBroker
  Accepts       : Nothing.
  Returns       : void 
  Abstraction   : This function reconnects to the broker. This function
                  get called on the pos-edge of the pulse.
  Modified by   : 24th Feb, 2021 : Ashraful
*/
#if 0
void Mqtt::tryReconnectToBroker() {
  // TODO: We should find and write the reason of non-connecting
  Serial.println("Connecting subscriber with broker..");
  while (!mqttClient.connected()) {
    // TODO: It might make sense to try reconnecting till a certain
    // number of times instead doing it indefinitely.
    // *getLogFile() << "Client ID = " << CLIENT_ID << std::endl;

    // Converting the std::string into char array since setServer
    // accepts only char[]. For some reason, it does not accept
    // char* which we can get using std::string.c_str()
    int arrSize = std::string(CLIENT_ID).size();
    char clientIDCharArray[arrSize];
    strcpy(clientIDCharArray, std::string(CLIENT_ID).c_str());

    // Appending the client ID to the string needs to be printed
    Serial.println("1: ClientID = " + String(clientIDCharArray));

    // if (mqttClient.connect(clientIDCharArray)) {
    if (mqttClient.connect(clientIDCharArray)) {
      // *getLogFile() << "Connected the subscriber with the broker";
      Serial.println("1: Connected the subscriber with the broker");

      // Converting the std::string into char array since setServer
      // accepts only char[]. For some reason, it does not accept
      // char* which we can get using std::string.c_str()
      arrSize = std::string(TOPIC_NAME).size();
      char topicNameArray[arrSize + 1];
      strcpy(topicNameArray, std::string(TOPIC_NAME).c_str());

      // Subscribe to topic
      mqttClient.subscribe(topicNameArray);
      // *getLogFile() << "Subscriber subscribed to the topic " << TOPIC_NAME << std::endl;
      Serial.println("1: Subscriber subscribed to the topic" + String(topicNameArray));

      // TODO: Why is this delay? Remove this.
      // delay(100);
    } else {
      Serial.println("1: Connection failed while connecting the subscriber \
with the broker.");
/*
      *getLogFile() << "Connection failed while connecting the subscriber \
with the broker." << std::endl;
*/
    }
  }
}
#endif

/*
  Function      : publishDataToBroker
  Accepts       : Nothing.
  Returns       : void 
  Abstraction   : This function reads the sensor pin value and publishes the data to the
                  broker. It gets called on the pos-edge of the pulse.

                  It also takes care of publishing only once in 500 mili-seconds.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::publishDataToBroker() {
  // *getLogFile() << "Publishing the data to the broker" << std::endl;
  long now = millis();
  if ((now - getMqttTime()) > TIMEFRAME) {
    // Set the data
    int sensorStatus = digitalRead(led->getSensorPin());
    setMqttData(sensorStatus ? PUBLISHER_SEND_MESSAGE_ON
                             : PUBLISHER_SEND_MESSAGE_OFF);

    int arrSize = getMqttData().size();
    char dataArray[arrSize + 1];
    strcpy(dataArray, getMqttData().c_str());

    mqttClient.publish(TOPIC_NAME, dataArray);
    // *getLogFile() << "Published the data to the broker" << std::endl;
    Serial.println("Published the data to the broker. Data is " + String(dataArray));
    setMqttTime(now);
  }
}

// Getters
/*
  Function      : getMqttServerAddress
  Accepts       : Nothing.
  Returns       : std::string 
  Abstraction   : This function returns the mqtt server address name.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::string Mqtt::getMqttServerAddress() {
  return mqttServer;
}

/*
  Function      : getMqttPortAddress
  Accepts       : Nothing.
  Returns       : int
  Abstraction   : This function returns the mqtt port address.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
int Mqtt::getMqttPortAddress() {
  return mqttPort;
}

/*
  Function      : getMqttData
  Accepts       : Nothing.
  Returns       : std::string 
  Abstraction   : This function returns the mqtt data which is published
                  by the publisher.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::string Mqtt::getMqttData() {
  return mqttData;
}

/*
  Function      : getMqttTime
  Accepts       : Nothing.
  Returns       : long
  Abstraction   : This function returns the last stored time of the operation
                  by the publisher.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
long Mqtt::getMqttTime() {
  return mqttTime;
}

/*
  Function      : getFilePtr
  Accepts       : void
  Returns       : std::ofstream
  Abstraction   : This function sets the time.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
std::ofstream* Mqtt::getLogFile() {
  return logFile;
}

// Setters
/*
  Function      : setMqttServerAddress
  Accepts       : std::string
  Returns       : void
  Abstraction   : This function sets the mqtt server address name.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setMqttServerAddress(std::string iServer) {
  mqttServer = iServer;
}

/*
  Function      : getMqttPortAddress
  Accepts       : int.
  Returns       : void
  Abstraction   : This function sets the mqtt port address.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setMqttPortAddress(int iPort) {
  mqttPort = iPort;
}

/*
  Function      : setMqttData
  Accepts       : std::string
  Returns       : void
  Abstraction   : This function sets the mqtt data.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setMqttData(std::string iData) {
  mqttData = iData;
}

/*
  Function      : setMqttTime
  Accepts       : long
  Returns       : void
  Abstraction   : This function sets the time.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setMqttTime(long iTime) {
  mqttTime = iTime;
}

/*
  Function      : setFileObject
  Accepts       : std::string
  Returns       : void
  Abstraction   : This function sets the time.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::setLogFile(std::ofstream* filePtr) {
  logFile = filePtr;
}

/*
  Function      : setMotorCommand
  Accepts       : char
  Returns       : void
  Abstraction   : This function sets the command to for motor.
  Modified by   : 14th March, 2022 : Ashraful
 */
void Mqtt::setMotorCommand(char iMotorCommand) {
  motorCommand = iMotorCommand;
}

/*
  Function      : myLoop
  Accepts       : Nothing
  Returns       : void
  Abstraction   : This function just calls the loop function of the mqtt client.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Mqtt::myLoop() {
  mqttClient.loop();
}
