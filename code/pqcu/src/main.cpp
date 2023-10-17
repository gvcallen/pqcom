#include <RadioLib.h>

SX1278 radio = new Module(10, 2, 9);

void setFlag(void);

int transmissionState = 0;

void setup() {
  Serial.begin(9600);

  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initializing ... "));
  
  int16_t state = radio.begin(434.0, 500.0, 8, 7, 0x12, 10, 8, 0);
  if (state == 0) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  // set the function that will be called
  // when packet transmission is finished
  radio.setPacketSentAction(setFlag);

  Serial.print(F("[SX1278] Sending first packet ... "));

  transmissionState = radio.startTransmit("Hello");

}

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;
void setFlag(void) {
  transmittedFlag = true;
  uint16_t flags = radio.getIRQFlags();

  Serial.print("Flags = ");
  Serial.println(flags);
}

int count = 0;

void loop() {
  // check if the previous transmission finished
  if(transmittedFlag) {
    // reset flag
    transmittedFlag = false;

    if (transmissionState == 0) {
      // packet was successfully sent
      Serial.println(F("transmission finished!"));

      // NOTE: when using interrupt-driven transmit method,
      //       it is not possible to automatically measure
      //       transmission data rate using getDataRate()

    } else {
      Serial.print(F("failed, code "));
      Serial.println(transmissionState);

    }

    // clean up after transmission is finished
    // this will ensure transmitter is disabled,
    // RF switch is powered down etc.
    // radio.finishTransmit();

    // wait a second before transmitting again
    delay(1000);

    // send another one
    Serial.print(F("[SX1278] Sending another packet ... "));

    // you can transmit C-string or Arduino string up to
    // 255 characters long
    String str = "Hello World! #" + String(count++);
    transmissionState = radio.startTransmit(str);

    // you can also transmit byte array up to 255 bytes long
    /*
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                        0x89, 0xAB, 0xCD, 0xEF};
      transmissionState = radio.startTransmit(byteArr, 8);
    */
  }
}