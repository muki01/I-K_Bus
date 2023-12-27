#include <avr/interrupt.h>
#include <IbusSerial.h>
#include <SoftwareSerial.h>
SoftwareSerial debugSerial(7, 8);
IbusSerial ibus;

byte source, length, destination, databytes[36];

static bool carLocked = false;
int top_Btn_Presed = 0;
int mid_Btn_Presed = 0;
static unsigned long lastTimeTopBtn = 0;
static unsigned long lastTimeMidBtn = 0;

void setup() {
  ibus.setIbusSerial(Serial);
  debugSerial.begin(9600);
  ibus.setIbusDebug(debugSerial);
  debugSerial.println(F("--IBUS reader--"));
  ibus.setIbusPacketHandler(packetHandler);
  ibus.sleepEnable(60);
  attachInterrupt(digitalPinToInterrupt(3), startTimer, CHANGE);
}
void loop() {
  ibus.run();
}

void packetHandler(byte *packet) {
  source = packet[0];
  length = packet[1];
  destination = packet[2];
  for (int i = 0, s = 3; i <= length - 3; i++, s++) {
    databytes[i] = packet[s];
  }

  if ((source == 0x00) && (destination == 0xBF) && (databytes[0] == 0x72) && (databytes[1] == 0x22)) {
    carLocked = false;
    unsigned long currentTime = millis();
    unsigned long timeSinceLastEntry = currentTime - lastTimeTopBtn;

    if (timeSinceLastEntry >= 14500) {
      top_Btn_Presed = 0;
    }
    if (top_Btn_Presed == 0) {
      ibus.write(ParkLights_And_Signals, sizeof(ParkLights_And_Signals));
      top_Btn_Presed = 1;
      lastTimeTopBtn = currentTime;
    } else {
      ibus.write(ParkLights_And_Signals_And_FogLights, sizeof(ParkLights_And_Signals_And_FogLights));
      top_Btn_Presed = 0;
      lastTimeTopBtn = currentTime;
    }
  }

  if ((source == 0x00) && (destination == 0xBF) && (databytes[0] == 0x72) && (databytes[1] == 0x12)) {
    top_Btn_Presed = 0;
    if (carLocked == false) {
      carLocked = true;
    } else if (carLocked) {
      mid_Btn_Presed++;
      unsigned long currentTime = millis();
      unsigned long timeSinceLastEntry = currentTime - lastTimeMidBtn;
      if (mid_Btn_Presed == 2 && timeSinceLastEntry <= 4000) {
        ibus.write(FollowMeHome, sizeof(FollowMeHome));
        mid_Btn_Presed = 0;
      } else if (timeSinceLastEntry > 4000) {
        mid_Btn_Presed = 1;
      }
      lastTimeMidBtn = currentTime;
    }
  }
}

void startTimer() {
  ibus.startTimer();
}