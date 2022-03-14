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
#ifndef Led_Header
#define Led_Header 1

/*
  Class           : Led
  Interfaced with : Mqtt have an pointer of this class
  Abstraction     : This returns the pin number on which we have connected our sensor.
  Modified by     : 24th Feb, 2021 : Ashraful
 */
class Led {
  int ledPin;
  int sensorPin;
  public:
    void setSensorPin(int);
    void setLedPin(int);
    void setPinStatus(int);
    int getLedPin();
    int getSensorPin();
  	int getPinStatus();

    Led();
    ~Led();
};

#endif
