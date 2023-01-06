#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <registers.h>

unsigned char iorq = 0x00;
unsigned char mreq = 0x00;
unsigned char rdwr = 0x00;
unsigned char rest = 0x00;

unsigned short addrBus = 0x0000;
unsigned char dataBus = 0x00;
