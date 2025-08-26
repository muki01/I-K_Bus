#ifndef IbusSerial_h
#define IbusSerial_h

#include "Arduino.h"
#include "HardwareSerial.h"
#include "RingBuffer.h"

#define IBUS_DEBUG

class IbusSerial {
 public:
  IbusSerial();
  ~IbusSerial();
  void setIbusSerial(HardwareSerial &newIbusSerial);
#if defined(IBUS_DEBUG)
  void setIbusDebug(Stream &newIbusDebug);
#endif
  void run();
  void write(const byte message[], byte size);
  void printDebugMessage(const char *debugPrefix);
  typedef void IbusPacketHandler_t(byte *packet);
  void setIbusPacketHandler(IbusPacketHandler_t newHandler);
  void contentionTimer();
  void startTimer();
  void sleepEnable(unsigned long sleepTime);
  byte calculateChecksum(const byte *data, byte length);
  void sleep();

 private:
  enum ibusFsmStates {
    FIND_SOURCE,    // Read source byte
    FIND_LENGTH,    // Read length byte
    FIND_MESSAGE,   // Read in main body of message
    GOOD_CHECKSUM,  // Process message if checksum good
    BAD_CHECKSUM,   // Debug print bad message if checksum bad
  } ibusState;

  void readIbus();
  void compareIbusPacket();
  void sendIbusPacket();
  void sendIbusMessageIfAvailable();
  HardwareSerial *IbusSerial;
#if defined(IBUS_DEBUG)
  Stream *IbusDebug;
#endif
  byte source;
  byte length;
  byte destination;
  byte ibusByte[40];
  boolean busInSync;
  static const byte packetGap = 10;
  byte *pData;
  IbusPacketHandler_t *pIbusPacketHandler;
};
#endif