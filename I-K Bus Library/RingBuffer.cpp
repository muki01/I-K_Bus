#include "RingBuffer.h"

RingBuffer::RingBuffer(int size)
{
  bufferSize = size;
  bufferTail = 0;
  bufferHead = 0;
  buffer_p = (byte *)malloc(size);
  memset(buffer_p, 0, size);
}

RingBuffer::~RingBuffer()
{
  if (buffer_p)
    free(buffer_p);
}

// public functions

int RingBuffer::available(void)
{
  int ByteCount = (bufferSize + bufferHead - bufferTail) % bufferSize;
  return ByteCount;
}

int RingBuffer::read(void)
{
  if (bufferHead == bufferTail)
  {
    return -1;
  }
  else
  {
    byte c = buffer_p[bufferTail];
    bufferTail = (bufferTail + 1) % bufferSize;
    if (bufferHead == bufferTail)
    {
      bufferTail = 0;
      bufferHead = 0;
    }
    return c;
  }
}

byte RingBuffer::write(int c)
{
  if ((bufferHead + 1) % bufferSize == bufferTail)
  {
    return -1;
  }
  buffer_p[bufferHead] = c;
  bufferHead = (bufferHead + 1) % bufferSize;
  return 0;
}

void RingBuffer::remove(int n)
{
  if (bufferHead != bufferTail)
  {
    bufferTail = (bufferTail + n) % bufferSize;
  }
}

int RingBuffer::peek(void)
{
  if (bufferHead == bufferTail)
  {
    return -1;
  }
  else
  {
    return buffer_p[bufferTail];
  }
}

int RingBuffer::peek(int n)
{

  if (bufferHead == bufferTail)
  {
    return -1;
  }
  else
  {
    return buffer_p[(bufferTail + n) % bufferSize];
  }
}