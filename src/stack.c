#include <stdio.h>
#include <stdlib.h>
#include <stack.h>
#include <registers.h>

unsigned char stack[256] = {0};

void pushToStack(unsigned char value){
	stack[++stackPointer] = value;
}

unsigned char popFromStack(){
	return stack[stackPointer--];
}

unsigned char incStackPointer(){
	stackPointer++;
	return stackPointer;
}

unsigned char decStackPointer(){
	stackPointer--;
	return stackPointer;
}
