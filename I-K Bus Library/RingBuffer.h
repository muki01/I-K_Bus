#include "Arduino.h"

#ifndef RingBuffer_h
#define RingBuffer_h


class RingBuffer
{
private:

	int bufferSize;
	unsigned int bufferHead, bufferTail;
	byte *buffer_p;
	
public:
	RingBuffer(int size);
        ~RingBuffer();
	int available(void);
	int peek(void);
	int peek(int);
	void remove(int);
	int read(void);
	byte write(int);
};
#endif
