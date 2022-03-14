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

#ifndef HEADERS
#define HEADERS 1
#define LED_PIN                    2
#define SENSOR_PIN                 27
#define BAUD_RATE                  115200
#define SERVER_ADDRESS             "192.168.0.103"
// #define SERVER_ADDRESS             "192.168.0.233"
#define SERVER_PORT                1883
#define TOPIC_NAME                 "/swa/sensor_status"
#define CLIENT_ID                  "Client1"
#define WIFI_NAME                  "OfficeBay"
#define WIFI_PASS                  "Aarone@123"
#define LOG_FILE_NAME              "/home/hemant/Remote_Operation_ESP32/data.log"
#define PUBLISHER_SEND_MESSAGE_ON  "ON"
#define PUBLISHER_SEND_MESSAGE_OFF "OFF"
#define TIMEFRAME                  200
#endif
