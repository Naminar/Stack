
#ifndef STACK_

#define STACK_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define ELEMENT_FMT "%d"
                             //OPEN BY HAND!!
//typedef int DATA;

struct Stack{
    size_t first_canary;

    DATA* data;
    size_t size;
    size_t capacity;

    size_t hash;

    size_t second_canary;
};

typedef struct Stack Stack;

//===============================================

const size_t CANARY = 19;
const size_t CONTROL_DIMENS = 20; //It was = 200
const size_t NULL_HASH = 0xdd233d4;
const size_t WITH_CANARY_CONTROL_DIMENS = CONTROL_DIMENS + 2;

//===============================================

DATA *const ERR_PTR    = (DATA*) 1;
const int ERR_RESIZE   = 0;
//const int ERR_POP_SIZE = 0;

//===============================================

int stack_resize    (Stack* stk)                                    ;
int stack_init      (Stack* stk, int capacity, void* stack_place)   ;
void stack_dtor     (Stack* stk)                                    ;
int stack_push      (Stack* stk, DATA  element)                     ;
int stack_pop       (Stack* stk, DATA* element)                     ;
void stack_dump     (Stack* stk, int, int, const char*, const char*);
int is_stack_spoiled(Stack* stk)                                    ;
void DragonHash     (Stack* stk)                                    ;
//===============================================

#endif
