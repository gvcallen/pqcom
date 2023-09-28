#include <SPI.h>
#include <LoRa.h>

// VCC	      3.3V
// GND	      GND
// SCK	      13
// MISO	      12
// MOSI	      11
// NSS	      10
// NRESET	    9
// DIO0	      2


void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(500E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("Connected successfully. Listening...");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Msg: '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("', RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}