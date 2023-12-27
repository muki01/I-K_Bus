#include "IbusSerial.h"

const byte senStaPin = 3;
const byte enablePin = 4;
const byte ledPin = 13;
volatile boolean clearToSend = false;
unsigned long ibusTimeToSleep;
boolean sleepEnabled;
unsigned long ibusSleepTime = millis();
unsigned long packetTimer = millis();
RingBuffer ibusReceiveBuffer(128);
RingBuffer ibusSendBuffer(64);

IbusSerial::IbusSerial() // constructor
{
  busInSync = false;
  ibusSleepTime = millis();
  packetTimer = millis();
  source = 0;
  length = 0;
  destination = 0;
  ibusState = FIND_SOURCE;
  sleepEnabled = false;
  pinMode(ledPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  digitalWrite(enablePin, HIGH);
  contentionTimer();
}

IbusSerial::~IbusSerial() // deconstructor
{
}

void IbusSerial::setIbusSerial(HardwareSerial &newIbusSerial)
{
  IbusSerial = &newIbusSerial;
  IbusSerial->begin(9600, SERIAL_8E1); // ibus always 9600 8E1
}

#if defined(IBUS_DEBUG)
void IbusSerial::setIbusDebug(Stream &newIbusDebug)
{
  IbusDebug = &newIbusDebug;
}
#endif

void IbusSerial::setIbusPacketHandler(IbusPacketHandler_t newHandler)
{
  pIbusPacketHandler = newHandler;
}

void IbusSerial::readIbus()
{
  if (IbusSerial->available())
  {
    ibusReceiveBuffer.write(IbusSerial->read());
  }
  switch (ibusState)
  {
  case FIND_SOURCE:
    if (ibusReceiveBuffer.available() >= 1)
    {
      source = ibusReceiveBuffer.peek(0);
      ibusState = FIND_LENGTH;
    }
    break;

  case FIND_LENGTH:
    if (ibusReceiveBuffer.available() >= 2)
    {
      length = ibusReceiveBuffer.peek(1);
      if (length >= 0x03 && length <= 0x24)
      { // Check if length byte between decimal 3 & 36
        ibusState = FIND_MESSAGE;
      }
      else
      {
        // remove source byte and start over
        ibusReceiveBuffer.remove(1);
      }
    }
    break;

  case FIND_MESSAGE:
    if (ibusReceiveBuffer.available() >= length + 2) // Check if enough bytes in buffer to complete message (based on length byte)
    {
      byte checksumByte = 0;
      for (int i = 0; i <= length; i++)
      {
        checksumByte ^= ibusReceiveBuffer.peek(i);
      }
      if (ibusReceiveBuffer.peek(length + 1) == checksumByte)
      {
        ibusSleepTime = millis(); // Restart sleep timer
        ibusState = GOOD_CHECKSUM;
      }
      else
      {
        ibusState = BAD_CHECKSUM;
      }
    }
    break;

  case GOOD_CHECKSUM:
    // only process messages we're interested in
    if (source != 0x50    // MFL
        && source != 0x68 // RAD
        && source != 0x18 // CDC
        && source != 0x6A // DSP
        && source != 0xC8 // TEL
        && source != 0xB0 // SES
        && source != 0xE8 // RLS
        && source != 0x44 // SES
        && source != 0x00 // RLS
    )
    {
      // remove unwanted message from buffer and start over
#ifdef IBUS_DEBUG
      IbusDebug->print(F("DISCARDED: "));
      for (int i = 0; i <= length + 1; i++)
      {
        if (ibusReceiveBuffer.peek(i) < 0x10)
        {
          IbusDebug->print(F("0"));
        }
        IbusDebug->print(ibusReceiveBuffer.peek(i), HEX);
        IbusDebug->print(F(" "));
      }
      IbusDebug->println();
#endif
      ibusReceiveBuffer.remove(length + 2);
      ibusState = FIND_SOURCE;
      return;
    }
    // read message from buffer
    for (int i = 0; i <= length + 1; i++)
    {
      ibusByte[i] = ibusReceiveBuffer.read();
    }
#ifdef IBUS_DEBUG
    // debug print good message
    printDebugMessage("Good Message -> ");
#endif
    busInSync = true;
    compareIbusPacket();
    ibusState = FIND_SOURCE;
    break;

  case BAD_CHECKSUM:
#ifdef IBUS_DEBUG
    // debug print bad message
    printDebugMessage("Message Bad -> ");
#endif
    // remove first byte and start over
    ibusReceiveBuffer.remove(1);
    ibusState = FIND_SOURCE;
    break;

  } // end of switch
} // end of readIbus

#ifdef IBUS_DEBUG
void IbusSerial::printDebugMessage(const char *debugPrefix)
{
  IbusDebug->print(debugPrefix);
  for (int i = 0; i <= length + 1; i++)
  {
    if (ibusByte[i] < 0x10)
    {
      IbusDebug->print(F("0"));
    }
    IbusDebug->print(ibusByte[i], HEX);
    IbusDebug->print(F(" "));
  }
  IbusDebug->println();
}
#endif

void IbusSerial::compareIbusPacket()
{
  byte *pData = &ibusByte[0];
  pIbusPacketHandler((byte *)pData);
}

void IbusSerial::write(const byte message[], byte size)
{
  ibusSendBuffer.write(size);
  for (int i = 0; i < size; i++)
  {
    ibusSendBuffer.write(pgm_read_byte(&message[i]));
  }
}

void IbusSerial::sendIbusMessageIfAvailable()
{
  if (clearToSend && ibusSendBuffer.available() > 0) // clearToSend &&
  {
    if (millis() - packetTimer >= packetGap)
    {
      sendIbusPacket();
      packetTimer = millis();
    }
  }
}

void IbusSerial::sendIbusPacket()
{
  int Length = ibusSendBuffer.read();
  if (digitalRead(senStaPin) == LOW && Length <= 32) // digitalRead(senStaPin) == LOW &&
  {
#if defined(IBUS_DEBUG)
    IbusDebug->println(F("TRANSMITING CODE"));
#endif
    for (int i = 0; i < Length; i++)
    {
      byte dataByte = ibusSendBuffer.read();
      IbusSerial->write(dataByte); // write byte to IBUS.
    }
  }
  else
  {
    ibusSendBuffer.remove(Length);
    return;
  }
}

void IbusSerial::sleepEnable(unsigned long sleepTime)
{
  ibusTimeToSleep = sleepTime * 1000;
  sleepEnabled = true;
}

void IbusSerial::sleep()
{
  if (sleepEnabled == true)
  {
    if (millis() - ibusSleepTime >= ibusTimeToSleep)
    {
      digitalWrite(enablePin, LOW); // Shutdown TH3122
    }
  }
}

void IbusSerial::run()
{
  readIbus();
  sendIbusMessageIfAvailable();
  sleep();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IbusSerial::contentionTimer()
{
#define START_TIMER2 TCCR2B |= (1 << CS22) | (1 << CS21) // //Set CS22 and CS21 bits for 256 prescaler
#define STOP_TIMER2 TCCR2B &= 0B11111000

  // initialize Timer1
  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B

  // set compare match register to desired timer count:
  OCR2A = 94; // Set timer to fire CTC interrupt after approx 1.5ms

  // turn on CTC mode:
  TCCR2B |= (1 << WGM21);

  // enable timer compare interrupt:
  TIMSK2 |= (1 << OCIE2A);
  pinMode(senStaPin, INPUT);
  // pIbusDebug->println(F("Arduino / Melexis"));
}

//========================

void IbusSerial::startTimer()
{
  if (digitalRead(senStaPin) == LOW)
  {
    START_TIMER2;
  }
  else if (digitalRead(senStaPin) == HIGH)
  {
    clearToSend = false;
    digitalWrite(ledPin, HIGH);
    STOP_TIMER2;
  }
}

//========================

ISR(TIMER2_COMPA_vect)
{
  clearToSend = true;
  digitalWrite(ledPin, LOW);
  STOP_TIMER2;
}
