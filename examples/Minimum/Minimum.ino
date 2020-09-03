#include "GreenBeacon.h"

void setup() {
  GreenBeacon beacon = GreenBeacon("0a1b2c3d4e");
  beacon.start("Hello!");
}

void loop() {
}
