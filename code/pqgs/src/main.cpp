#include <LoRaLib.h>
#include <gel.h>

void setFlag(void);

SX1278 radio = new Module(27, 15, 13);

size_t totalBits = 0;
volatile bool receivedFlag = false;
volatile bool receivedOne = false;
unsigned long firstReceiveTime = 0;

uint8_t expectedPayload[] =
  "00000#"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "abcdefghijklmnopqrstuvwxyz\n"
  "Done\n";

void setup() {
  Serial.begin(115200);
  
  while (!Serial);
  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initializing ... "));

  int state = radio.begin(427.0, 500.0, 8, 4 + 2, 0x12, 10, 150, 8);
  radio.implicitHeader(sizeof(expectedPayload));
  
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }

  radio.setDio0Action(setFlag);
  // radio.setPacketReceivedAction(setFlag);

  Serial.print(F("[SX1278] Starting to listen ... "));
  state = radio.startReceive();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void setFlag(void) {
  receivedFlag = true;
  if (!receivedOne)
  {
    firstReceiveTime = millis();
    receivedOne = true;
  }
}

#define NUM_PACKET_AVG 10
size_t packetReceiveTimes[NUM_PACKET_AVG] = {};
size_t numPackets = 0;
void loop() {
  if(receivedFlag) {
    receivedFlag = false;

    String str;
    int state = radio.readData(str);

    unsigned long newestReceiveTime = packetReceiveTimes[numPackets++ % NUM_PACKET_AVG] = millis();
    unsigned long oldestReceiveTime;
    size_t numPacketsAvg;
    if (numPackets >= NUM_PACKET_AVG)
    {
      numPacketsAvg = NUM_PACKET_AVG;
      oldestReceiveTime = packetReceiveTimes[numPackets % NUM_PACKET_AVG];
    }
    else
    {
      numPacketsAvg = numPackets;
      oldestReceiveTime = packetReceiveTimes[0];
    }

    unsigned long deltaTime = newestReceiveTime - oldestReceiveTime;
    float bitRate = (float)(numPacketsAvg * 8 * 255) / ((float)deltaTime / 1000.0);
    Serial.println("***** Running at " + String(bitRate) + " bps *****");

    if (state == ERR_NONE || state == ERR_CRC_MISMATCH) {
      // packet was successfully received
      Serial.println("[SX1278] Received packet #" + str.substring(0, 5));
      if (state == ERR_CRC_MISMATCH)
        Serial.println(F("[SX1278] CRC error!")); 

      // print data of the packet
      int expectedNum = sizeof(expectedPayload);
      int receivedNum = 0;
      const int offset = 6;
      for (int i = offset; i < expectedNum; i++)
      {
        if (str[i] == expectedPayload[i])
          receivedNum++;
      }
      float prr = (float)(receivedNum) / (float)(expectedNum - offset);

      Serial.print(F("[SX1278] RSSI:\t\t"));
      Serial.print(radio.getRSSI());
      Serial.println(F(" dBm"));

      // print SNR (Signal-to-Noise Ratio)
      Serial.print(F("[SX1278] SNR:\t\t"));
      Serial.print(radio.getSNR());
      Serial.println(F(" dB"));

      // print PRR
      Serial.print(F("[SX1278] PRR:\t\t"));
      Serial.print(prr * 100);
      Serial.println(F(" %"));

      // print frequency error
      // Serial.print(F("[SX1278] Frequency error:\t"));
      // Serial.print(radio.getFrequencyError());
      // Serial.println(F(" Hz"));

    } else {
      // some other error occurred
      Serial.print(F("[SX1278] Failed, code "));
      Serial.println(state);
    }

    Serial.println();
    state = radio.startReceive();
  }
}