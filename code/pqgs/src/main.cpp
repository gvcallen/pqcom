#include <SPI.h>
#include <LoRa.h>

// SX1278 has the following connections:
uint32_t nss = 27;
uint32_t dio0 = 15;
uint32_t reset = 13;

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  delay(1000);

  Serial.println("LoRa Sender");

  LoRa.setPins(nss, reset, dio0);

  if (!LoRa.begin(500E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setTxPower(10);
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(2000);
}