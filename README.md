# line-simple-beacon-esp32

LINE Simple Beacon library for ESP32 (Arduino core)

This is unofficial library for ESP32 boards, conforming to [LINE Simple Beacon (Official)](https://github.com/line/line-simple-beacon/blob/master/README.en.md).

## Getting Started

1. Web: Create your LINE official account.  
  [https://manager.line.biz/](https://manager.line.biz/)
2. App: Add your official account as friend.  
3. App: Make available LINE Beacon on your smartphone.  
  `LINE app` > `Settings` > `Privacy` > `Provide usage data` > fill checkbox at `LINE Beacon`
4. PC: Issue "LINE Simple Beacon Hardware ID" from below.  
  [https://manager.line.biz/beacon/register](https://manager.line.biz/beacon/register)
5. Arduino IDE: Set the issued ID to variable "hwid" in sample sketches as 5 bytes of array.  
  e.g. Hardware ID: `0123456789` -> `hwid[5] = {0x01, 0x23, 0x45, 0x67, 0x89}`
6. Arduino IDE: Upload the sketch to your ESP32 based board.  
7. Programming: Develop your backend (server-side) script using LINE messaging API to handle beacon event.  
  [https://developers.line.biz/en/reference/messaging-api/#beacon-event](https://developers.line.biz/en/reference/messaging-api/#beacon-event)

## Example

```
// Set your hardware ID
const char hwid[5] = {0x01, 0x23, 0x45, 0x67, 0x89};
// Create beacon instance
LineSimpleBeacon beacon = LineSimpleBeacon(hwid);
// Set advertise message
beacon.setMessage("hey");
// Start advertising
beacon.start();
```

## Dependency

- BLEDevice.h [(ESP32\_BLE\_Arduino)](https://github.com/nkolban/ESP32_BLE_Arduino)

No need additional installation if you installed [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32) from boards manager on Arduino IDE.

## API

### LineSimpleBeacon(const char hwid[5], const String device_name = "LINE Simple Beacon")

`hwid` : Issued LINE Simple Beacon hardware ID. It must be 5 bytes of array.  
`device_name` : (optional) BLE Device name.

### void setMessage(const String message)

`message` : The payload message (Max length: 13 bytes). This string will be set to `beacon.dm` on LINE Messaging API's beacon event. See [Beacon event](https://developers.line.biz/en/reference/messaging-api/#beacon-event).

### void start()

Start advertising.

### void stop()

Stop advertising.

## License

This project is licensed under the MIT License - see the LICENSE.md file for details.
