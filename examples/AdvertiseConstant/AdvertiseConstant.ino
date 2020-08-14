#include "GreenBeacon.h"

/**
 * 1. Web: Create your LINE official account
 *    https://manager.line.biz/
 * 2. App: Add your official account as friend
 * 3. App: Make available LINE Beacon on your smartphone
 *    LINE app > Settings > Privacy > Provide usage data > fill checkbox "LINE Beacon"
 * 4. PC: Issue "LINE Simple Beacon Hardware ID" from below
 *    https://manager.line.biz/beacon/register
 * 5. Arduino IDE: Set the issued ID to variable "hwid" as 5 bytes of array
 *    e.g. Hardware ID: 0123456789 -> hwid[5] = {0x01, 0x23, 0x45, 0x67, 0x89}
 * 6. Arduino IDE: Upload this sketch to your ESP32 based board
 * 7. Programming: Develop your backend script using LINE messaging API to handle beacon event
 *    https://developers.line.biz/en/reference/messaging-api/#beacon-event
 */

const char hwid[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
GreenBeacon beacon = GreenBeacon(hwid);

void setup() {
  beacon.setMessage("Hello"); // max 13 bytes
  beacon.start();
}

void loop() {
  // do something..
  delay(50);
}
