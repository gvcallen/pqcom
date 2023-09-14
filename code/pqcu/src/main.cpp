#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

const int PIN_LED = 3;
float ledBrightness;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    Serial.println("LoRa Receiver");

    if (!LoRa.begin(433E6)) {
        Serial.println("Starting LoRa failed!");
        while (1);
    }

    Serial.println("Successfully initialized LoRa");
    pinMode(PIN_LED, OUTPUT);
    ledBrightness = 0.0;
}

void loop() {
    analogWrite(PIN_LED, (int)(255 * ledBrightness));
    delay(100);

    // try to parse packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // received a packet
        Serial.print("Received packet '");

        // read packet
        while (LoRa.available()) {
          Serial.print((char)LoRa.read());
        }

        // print RSSI of packet
        Serial.print("' with RSSI ");
        Serial.println(LoRa.packetRssi());
    }
}