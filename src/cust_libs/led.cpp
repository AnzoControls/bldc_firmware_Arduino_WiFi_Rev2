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
#include "cust_libs/led.h"
#include "cust_libs/headers.h"

/*
  Function      : setLedPin
  Accepts       : int
  Returns       : None
  Abstraction   : This sets the pin number on which we have connected our LED.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Led::setLedPin(int pinNumber) {
  ledPin = pinNumber;
}

/*
  Function      : setSensorPin
  Accepts       : int
  Returns       : None
  Abstraction   : This sets the pin number on which we have connected our sensor.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
void Led::setSensorPin(int pinNumber) {
  sensorPin = pinNumber;
}

/*
  Function      : getLedPin
  Accepts       : int
  Returns       : None
  Abstraction   : This returns the pin number on which we have connected our LED.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
int Led::getLedPin() {
  return ledPin;
}

/*
  Function      : getSensorPin
  Accepts       : int
  Returns       : None
  Abstraction   : This returns the pin number on which we have connected our sensor.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
int Led::getSensorPin() {
  return sensorPin;
}

void Led::setPinStatus(int status) {
}

int Led::getPinStatus() {
	return 0;
}

/*
  Function      : Led
  Accepts       : None
  Returns       : None
  Abstraction   : Constructor for LED class.
  Modified by   : 24th Feb, 2021 : Ashraful
 */
Led::Led() {
  setLedPin(LED_PIN);
  setSensorPin(SENSOR_PIN);
}
