#ifndef ASSEMBLER_H_
#define ASSEMBLER_H_

#define MAX_FILE_SIZE 5 * 1024

#include <stdio.h>

char opcodes[16][4] = {
	{"NOP"},
	{"PSH"},
	{"DUP"},
	{"DSP"},
	{"CMP"},
	{"ADD"},
	{"BRL"},
	{"NND"},
	{"HNE"},
	{"HOP"},
	{"LZF"},
	{"OUT"},
	{"OIN"},
	{"STO"},
	{"LOD"},
	{"HLT"}
};

char opvals[16] = {
	0x00, 0xFF, 0xCC, 0x0A, 0x55, 0xC3, 0x18, 0xE7, 0x48, 0x84, 0xEE, 0x02, 0x04, 0x08, 0x10, 0xBB	
};

char * getFile(FILE * fp);

char * findOpcodes(char * input);

void assemble(char * source, FILE * fpout);

#endif
