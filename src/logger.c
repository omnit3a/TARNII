#include <stdio.h>
#include <stdlib.h>
#include <registers.h>
#include <io.h>
#include <logger.h> 

void writeState(FILE * fp){
	fprintf(fp,"Program Counter: %X | ",programCounter);
	fprintf(fp,"Stack Pointer: %X\n",stackPointer);
	fprintf(fp,"Zero Flag: %X | ",zeroFlag);
	fprintf(fp,"Carry Flag: %X | ",carryFlag);
	fprintf(fp,"Equal Flag: %X\n",equalFlag);
}

void writeIO(FILE * fp){
	fprintf(fp,"###\n");
	fprintf(fp,"PC %X\n",programCounter);
	fprintf(fp,"ADDR %X\n",addrBus);
	fprintf(fp,"DATA %X\n",dataBus);
	fprintf(fp,"IORQ %X\n",iorq);
	fprintf(fp,"MREQ %X\n",mreq);
	fprintf(fp,"RDWR %X\n",rdwr);
	fprintf(fp,"REST %X\n",rest);
}
