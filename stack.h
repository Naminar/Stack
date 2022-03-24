
#ifndef STACK_

#define STACK_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ELEMENT_FMT "%d"
                                  //OPEN BY HAND!!
typedef int DATA;

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

class cStack{

    private:

    size_t first_canary;

    DATA* data;
    size_t size;
    size_t capacity;

    size_t hash;

    size_t second_canary;

    //========functions======

    public:

    explicit cStack(int capacity, void* stack_place = NULL)  ;
            ~cStack()                                        ;

    int  stack_resize    ()                                  ;
    int  is_stack_spoiled()                                  ;
    int  stack_push      (DATA  element)                     ;
    int  stack_pop       (DATA* element)                     ;

    private:

    void stack_dump      (int, int, const char*, const char*);
    void DragonHash      ()                                  ;
};

#endif
