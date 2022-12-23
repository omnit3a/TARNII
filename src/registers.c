#include <stdio.h>
#include <stdlib.h>
#include <registers.h>

unsigned short programCounter = 0x0000;
unsigned char stackPointer = 0x00;

unsigned char zeroFlag = 0x00;
unsigned char carryFlag = 0x00;
unsigned char equalFlag = 0x00;
