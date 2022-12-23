#include <stdio.h>
#include <stdlib.h>
#include <registers.h>
#include <io.h>
#include <logger.h> 

void writeState(FILE * fp){
	fprintf(fp,"Program Counter: %x | ",programCounter);
	fprintf(fp,"Stack Pointer: %x\n",stackPointer);
	fprintf(fp,"Zero Flag: %x | ",zeroFlag);
	fprintf(fp,"Carry Flag: %x | ",carryFlag);
	fprintf(fp,"Equal Flag: %x\n",equalFlag);
}
