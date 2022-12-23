#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE 256

extern unsigned char stack[256];

void pushToStack(unsigned char value);
unsigned char popFromStack();

//return value of stack pointer after increment/decrement
unsigned char incStackPointer();
unsigned char decStackPointer();

#endif
