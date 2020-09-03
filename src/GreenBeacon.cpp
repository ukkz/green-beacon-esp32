#include "GreenBeacon.h"

GreenBeacon::GreenBeacon() {}

GreenBeacon::GreenBeacon(const String hwid, const String device_name)
{
  // Beacon initialize
  init(device_name);
  // Set Hardware ID
  setHwid(hwid);
}

void GreenBeacon::setHwid(const String hwid)
{
  if (hwid.length() != 10)
  {
    log_e("Invalid length of Hardware ID (must be 10 chars) : %s", hwid.c_str());
    return;
  }
  char buf[11];
  hwid.toCharArray(buf, 11); // buf[10] = \0
  // char (string) array to binary array
  for (byte i = 0; i < 5; i++)
  {
    char msb = buf[2 * i];
    char lsb = buf[2 * i + 1];
    char bt = 0;
    // ms byte
    if (msb >= 48 && msb <= 57)
    {
      // 0 ~ 9
      bt += ((msb - 48) * 16);
    }
    else if (msb >= 65 && msb <= 70)
    {
      // A ~ F
      bt += ((msb - 55) * 16);
    }
    else if (msb >= 97 && msb <= 102)
    {
      // a ~ f
      bt += ((msb - 87) * 16);
    }
    else
    {
      // error
      log_e("Invalid value of Hardware ID (not HEX char) at index %d : %s", (2 * i), hwid.c_str());
      memset(rawData.hardware_id, 0, 5);
      return;
    }
    // ls byte
    if (lsb >= 48 && lsb <= 57)
    {
      // 0 ~ 9
      bt += (lsb - 48);
    }
    else if (lsb >= 65 && lsb <= 70)
    {
      // A ~ F
      bt += (lsb - 55);
    }
    else if (lsb >= 97 && lsb <= 102)
    {
      // a ~ f
      bt += (lsb - 87);
    }
    else
    {
      // error
      log_e("Invalid value of Hardware ID (not HEX char) at index %d : %s", (2 * i + 1), hwid.c_str());
      memset(rawData.hardware_id, 0, 5);
      return;
    }
    // set
    rawData.hardware_id[i] = bt;
  }
}

void GreenBeacon::init(const String device_name)
{
  // Create packet body
  rawData.header_flags[0] = 0x02;        // Length + AD_TYPE(flags)
  rawData.header_flags[1] = 0x01;        // Length + AD_TYPE(flags)
  rawData.ad_type_flags = 0x06;          // flags: LE General Discoverable Mode(2) + BR/EDR Not Supported(4)
  rawData.header_manufacturer[0] = 0x03; // Length + AD_TYPE(Complete list of 16-bit UUIDs available)
  rawData.header_manufacturer[1] = 0x03; // Length + AD_TYPE(Complete list of 16-bit UUIDs available)
  rawData.manufacturer_id_1[0] = 0x6f;   // LINE Corp(0xFE6F)
  rawData.manufacturer_id_1[1] = 0xfe;   // LINE Corp(0xFE6F)
  rawData.service_data_length = 0x0b;    // Data length: 0x0A(0byte)~0x17(13bytes)
  rawData.ad_type_service_data = 0x16;   // AD_TYPE(Service Data)
  rawData.manufacturer_id_2[0] = 0x6f;   // LINE Corp(0xFE6F)
  rawData.manufacturer_id_2[1] = 0xfe;   // LINE Corp(0xFE6F)
  rawData.line_beacon_frame_id = 0x02;   // LINE Beacon Frame(0x02)
  memset(rawData.hardware_id, 0, 5);     // Line Simple Beacon Hardware ID
  rawData.tx_power = 0x7f;               // TX Signal power(fixed as 0x7f)
  memset(rawData.device_message, 0, 13); // Message(default=0x00)
  // Set payload message
  memset(&payload[0], 0, 13);
  // Advertising status
  adv_on = false;
  // BLEDevice initialize
  if (!BLEDevice::getInitialized())
    BLEDevice::init(device_name.c_str());
  // Pre getAdvertising
  setMessage("");
}

std::string GreenBeacon::getAdvPacket()
{
  return std::string((char *)&rawData, sizeof(rawData));
}

void GreenBeacon::setMessage(const String message)
{
  // pause advertising
  if (adv_on)
    advertising->stop();
  // message -> char array in the packet (max 13bytes)
  message.toCharArray(payload, 13);
  memcpy(&rawData.device_message[0], &payload[0], 13);
  rawData.service_data_length = 0x0a + (char)message.length();
  // set data to advertising packet
  advData = BLEAdvertisementData();
  advData.addData(getAdvPacket());
  // set packet for advertising
  advertising = BLEDevice::getAdvertising();
  advertising->setAdvertisementData(advData);
  // resume advertising
  if (adv_on)
    advertising->start();
}

void GreenBeacon::start()
{
  advertising->start();
  adv_on = true;
}

void GreenBeacon::start(const String message)
{
  setMessage(message);
  advertising->start();
  adv_on = true;
}

void GreenBeacon::stop()
{
  advertising->stop();
  adv_on = false;
}
