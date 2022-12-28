#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assembler/assembler.h>

int fileSize = 0;

int main(int argc, char ** argv){
	
	//make sure enough parameters were passed
	if (argc < 2){
		fprintf(stderr, "No parameters were passed.\n Must pass an input file.\n");
		return 1;
	}
	if (argc < 3){
		fprintf(stderr, "No output file was passed\n");
		return 1;
	}

	//open input file
	FILE * fp = fopen(argv[1],"r");
	FILE * fpout = fopen(argv[2], "w");
	
	//check if input file exists
	if (fp == NULL || fpout == NULL){
		fprintf(stderr, "The input file that was passed does not exist\n");
		return 1;
	}
	assemble(findOpcodes(getFile(fp)), fpout);
	fclose(fp);
	fclose(fpout);
	return 0;

}
//return the contents of a file
char * getFile(FILE * fp){
	char * ret;
	unsigned short pos = 0;
	char ch;
	while ((ch = fgetc(fp)) != EOF){
    		ret[pos] = ch;
		pos++;
	}
	return ret;
}

char * findOpcodes(char * input){
	char * ret;
	unsigned int pos = 0;
	int prevIsOpcode = 0;
	char tempOp = 0;
	char tempArg = 0;
	char * token = strtok(input, " \n");	
	while (token != NULL){
		for (int i = 0 ; i < 16 ; i++){
			if (strcmp(token, opcodes[i]) == 0){
				tempOp = opvals[i];
				fileSize++;
				ret[pos++] = tempOp;
				if (i == 1 || i == 11){
					token = strtok(NULL, " \n");
					tempArg = (int) strtol(token, NULL, 16);	
					ret[pos++] = tempArg;
					fileSize++;	
				} else {
					ret[pos++] = 0x00;
					fileSize++;
				}
				break;
			}
		}
		token = strtok(NULL, " \n");
	}
	return ret;
}

void assemble(char * source, FILE * fpout){
	char temp[fileSize];
	unsigned int pos = 0;
	while (pos < fileSize){
		temp[pos] = source[pos];
		pos++;
	}
	fwrite(temp, 1, fileSize, fpout);
}
