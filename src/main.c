#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opcodes.h>
#include <ram.h>
#include <io.h>
#include <registers.h>
#include <stack.h>
#include <logger.h>

int main(int argc, char ** argv){

	int usingIO = 0;

	if (argc <= 2){
		printf("No arguments were passed\n Must pass program file then output file\n");
		return 1;
	}

	if (argc == 4 && !strcmp("-io",argv[3])){
		usingIO = 1;
	}

	//open files
	FILE * fp = fopen(argv[1],"r");
	FILE * log = fopen(argv[2],"w");
	//check if both files exist
	if (fp == NULL || log == NULL){
		printf("One or more of the passed files do not exist or could not be accessed\n");
		return 1;
	}
	
	//load program file into MEMORY
	unsigned char temp = 0;
	unsigned int pos = 0x02;
	while(1){
		temp = fgetc(fp);
		memory[pos] = temp;
		if (temp == HLT){
			break;
		}
		pos++;	
	}
	//run code
	iorq = 0x01;

	unsigned short tempAddr = 0x0000;
	unsigned char tempData = 0x00;
	unsigned char tempReg = 0x00;
	unsigned char tempRegB = 0x00;
	programCounter = 0x02;

	unsigned char droppedLSB = 0x00;
	unsigned char droppedMSB = 0x00;

	// print out what each column represents in the running log
	rest = 0x01;

	while (1){

		tempAddr = 0x0000;
		tempData = 0x00;
		tempReg = 0x00;
		tempRegB = 0x00;
		
		addrBus = 0x0000;
		dataBus = 0x00;
		mreq = 0x00;
		iorq = 0x01;
		rdwr = 0x00;

		// print out the state of the cpu while running a program
		switch (memory[programCounter]){
			case NOP:
				programCounter+=2;
				break;
			case PSH:
				tempData = memory[programCounter+1];
				pushToStack(tempData);
				fprintf(log,"STACK PUSH RESULT: 0x%x\n",tempData);
				programCounter+=2;
				break;
			case DUP:
				pushToStack(stack[stackPointer]);
				fprintf(log,"STACK DUPLICATE RESULT: 0x%x\n",stack[stackPointer]);
				programCounter+=2;
				break;
			case DSP:
				stackPointer--;
				programCounter+=2;
				break;
			case CMP:
				tempReg = popFromStack();
				tempRegB = popFromStack();
				equalFlag = (tempReg == tempRegB);
				zeroFlag = (!tempReg && !tempRegB);
				programCounter+=2;
				break;
			case ADD:
				tempReg = popFromStack();
				tempRegB = popFromStack();
				tempReg = tempReg + tempRegB + carryFlag;
				pushToStack(tempReg);
				fprintf(log,"ADDITION WITH CARRY RESULT: 0x%x\n",tempReg);
				programCounter+=2;
				break;
			case BRL:
				tempReg = popFromStack();
				tempRegB = popFromStack();
				for (int i = 0 ; i < tempRegB ; i++){
					droppedMSB = (tempReg >> 7 ) & 1;
					tempReg = (tempReg << 1) | droppedMSB;
				}
				pushToStack(tempReg);
				fprintf(log,"BIT ROTATE LEFT BY %x RESULT: 0x%x\n",tempRegB,tempReg);
				programCounter+=2;
				break;
			case NND:
				tempReg = popFromStack();
				tempRegB = popFromStack();
				tempReg = ~(tempReg & tempRegB);
				pushToStack(tempReg);
				fprintf(log,"BITWISE NAND RESULT: 0x%x\n",tempReg);
				programCounter+=2;
				break;
			case HNE:
				tempReg = popFromStack();
				tempAddr = popFromStack() * 16;
			      	tempAddr |= tempReg;
				if (equalFlag == 0){
					programCounter = tempAddr;
					fprintf(log,"CONDITIONAL HOP RESULT: 0x%x\n",tempAddr);
				} else {
					programCounter+=2;
				}
				break;
			case HOP:
				tempReg = popFromStack();
				tempAddr = popFromStack() * 16;
			      	tempAddr |= tempReg;
				fprintf(log,"UNCONDITIONAL HOP RESULT: 0x%x\n",tempAddr);
				programCounter = tempAddr;
				break;
			case LZF:
				tempReg = popFromStack();
				tempRegB = popFromStack();
				switch(memory[programCounter+1]){
					case 0x00:
						zeroFlag = tempReg;
						break;
					case 0x01:
						carryFlag = tempReg;
						break;
					case 0x02:
						equalFlag = tempReg;
						break;
				}
				programCounter+=2;
				break;
			case OUT:
				if (usingIO){
					tempReg = popFromStack();
					tempRegB = popFromStack();
					printf("%c",tempReg);
				}
				programCounter+=2;
				break;
			case OIN:
				if (usingIO){
					mreq = 0x01;
					iorq = 0x00;
					//load data bus
					dataBus = getc(stdin);
					pushToStack(dataBus);
				}
				programCounter+=2;
				break;
			case STO:
				break;
			case LOD:
				break;
			case HLT:
				fprintf(log, "\nHALT HALT HALT HALT HALT\n\n");
				fclose(fp);
				fclose(log);
				return 0;
		}
		writeState(log);
	}
	fprintf(log,"\nHALT HALT HALT HALT HALT\n\n");

	fclose(fp);
	fclose(log);
	return 0;
}
