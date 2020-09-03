#ifndef ARDUINO_ARCH_ESP32
#error Cannot use this GreenBeacon library in except the environment "Arduino core for the ESP32"
#endif
#include <Arduino.h>
#include <BLEDevice.h>

class GreenBeacon
{
private:
  struct
  {
    char header_flags[2];
    char ad_type_flags;
    char header_manufacturer[2];
    char manufacturer_id_1[2];
    char service_data_length;
    char ad_type_service_data;
    char manufacturer_id_2[2];
    char line_beacon_frame_id;
    char hardware_id[5];
    char tx_power;
    char device_message[13];
  } __attribute__((packed)) rawData;
  char payload[13];
  BLEAdvertisementData advData;
  BLEAdvertising *advertising;
  std::string getAdvPacket();
  bool adv_on;

public:
  GreenBeacon();
  GreenBeacon(const String hwid, const String device_name = "Green Beacon");
  void init(const String device_name = "Green Beacon");
  void setHwid(const String hwid);
  void setMessage(const String message);
  void start();
  void start(const String message);
  void stop();
};
