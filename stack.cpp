
#include "stack.h"

cStack::cStack(int capacity, void* stack_place)
{
    if(capacity <= 0)
    {
        printf(" Your capacity is wrong, it must be positive.");

        return;//exit(1);
    }

    if (stack_place)                                                        //change position in memory
        this->data = (DATA*) stack_place;//calloc(capacity + 2, sizeof(DATA)); //the space for canary
    else
        this->data = (DATA*) calloc(capacity + 2, sizeof(DATA));

    assert(this->data);

    this->capacity = capacity;
    this->size = 0;

    this->data[0] = CANARY;
    this->data[capacity + 1] = CANARY;

    this->first_canary  = CANARY;
    this->second_canary = CANARY;

    DragonHash();
}

cStack::~cStack()
{
    free(this->data);

    this->data = ERR_PTR;
}

int cStack::stack_push(DATA element)
{
    int key = 0;

    if(key = is_stack_spoiled())
    {
        stack_dump(key, __LINE__, __FILE__, __PRETTY_FUNCTION__);
    }

    if(this->size >= this->capacity)
        if(!stack_resize())
            return ERR_RESIZE;

    this->data[this->size + 1] = element;

    ++(this->size);

    DragonHash();

    return 1;
}

int cStack::stack_pop(DATA* element)
{
    assert(this->size >= 1);

    int key = 0;

    if(key = is_stack_spoiled())
    {
        stack_dump(key, __LINE__, __FILE__, __PRETTY_FUNCTION__);
    }

    *element = this->data[this->size]; //go to the cell taking into account the canary

    //if(this->size == 0)
    //   return ERR_POP_SIZE;   may change assert

    --(this->size);

    DragonHash();

    return 1;
}

int cStack::stack_resize()
{
    this->data = (DATA*) realloc(this->data, (this->capacity + 1) * 2
                                            * sizeof(DATA));  //size was changed

    if(this->data == NULL)
        return 0;

    this->capacity = 2 * this->capacity;
    this->data[this->capacity + 1] = CANARY;

    return 1;
}

void cStack::stack_dump(int key, int line, const char* file, const char* function)
{
    printf("ERROR WAS HAPPENED IN FUNCTION:\n%s\n LINE = %d\n FILE = %s\n\n", function, line, file);

    switch(key)
    {
        case -1:
        {
            printf("YOUR STRUCT CANARY WAS CHANGED!!!");

            break;
        }

        case -2:
        {
            printf("YOUR DATA CANARY WAS CHANGED!!!!!!");

            break;
        }

        case -3:
        {
            printf("SIZE OF DATA BIGGER THAN CONTROL_DIMENS!!! GO AWAY!!! SAVE YOUR (dark) SOULS!!!");

            break;
        }

        case -4:
        {
            printf("CAPACITY OF DATA BIGGER THAN CONTROL_DIMENS!!! ZOMBIE EMERGENCY!!!!!!!!");

            break;
        }

        case -5:
        {
            printf("SIZE BIGGER THAN CAPACITY. THAT'S NOT SO GOOD. FORMATTING YOUR DRIVES...");

            break;
        }

        case -6:
        {
            printf("DATA POINTER IS NULL. SEND $100 TO THE AUTHOR.");

            break;
        }

        case -7:
        {
            printf("HASH WAS CHANGED. GO LEARN MATHAN, BABY");

            break;
        }

        case -8:
        {
            printf("ERROR IN CONSTRUCTING HASH. SHOUT AT SOMEONE!"
                   "AAAAAAAAAAAAAAAAAAA!");

            break;
        }

        default:
        {
            printf("DUMP ERROR. I CANT BEAR IT. ABORTING... (no)");

            break;
        }
    }

    printf("\n\nDUMP RESULT:"                    "\n"
           "first canary:   %3d;  REAL CANARY = %d\n"
           "second canary:  %3d;  REAL CANARY = %d\n"
           "capacity:       %3d"                 "\n"
           "size:           %3d"                 "\n"
           "data[%p]\n{ \n",

            this->first_canary,
            CANARY,
            this->second_canary,
            CANARY,
            this->capacity,
            this->size,
            this->data);

    int ind_capacity = this->capacity;

    printf("  data[%d] = " ELEMENT_FMT " This is a CANARY; "
           "REAL CANARY = %d\n", ind_capacity + 1, this->data[ind_capacity + 1], CANARY);

    for (; ind_capacity > 0; --ind_capacity)
    {
        printf("  data[%d] = " ELEMENT_FMT "\n", ind_capacity, this->data[ind_capacity]);

    }

    printf("  data[%d] = " ELEMENT_FMT " This is a CANARY; "
           "REAL CANARY = %d\n} \n", 0, this->data[0], CANARY);

    return;//exit(2);
}

int cStack::is_stack_spoiled()
{
    if(this->first_canary != CANARY || this->second_canary != CANARY)
        return -1;

    if(this->data[0] != CANARY || this->data[this->capacity + 1] != CANARY)
        return -2;

    if(this->size > CONTROL_DIMENS)
        return -3;

    if(this->capacity > CONTROL_DIMENS)
        return -4;

    if(this->size > this->capacity)
        return -5;

    if(this->data == NULL)
        return -6;

    //////////////////////////////////

    size_t hash_copy = this->hash;

    DragonHash();

    if(hash_copy != this->hash)
        return -7;

    return 0;
}


void cStack::DragonHash()
{
    this->hash = 0;

    size_t records_key = 0;

    const unsigned char* struct_records = (const unsigned char*) this;
    const unsigned char* stack_data     = (const unsigned char*) this->data;

    for(size_t ind = 3; ind < sizeof(cStack); ind++)
    {
        records_key += 2 * struct_records[ind - 1] + struct_records[ind - 2] % 2 + struct_records[ind - 3];
    }

    switch(records_key % 4)
    {
        case 0:
        {
            records_key = records_key << 4 + 1;

            break;
        }

        case 1:
        {
            records_key = records_key << 8 + 3;

            break;
        }

        case 2:
        {
            records_key = records_key << 12 + 5;

            break;
        }

        case 3:
        {
            records_key = records_key << 16 + 7;

            break;
        }

        default:
        {
            stack_dump(-8, __LINE__, __FILE__, __PRETTY_FUNCTION__);

            break;
        }
    }

    size_t data_key = NULL_HASH;

    const size_t size_converter_value = sizeof(DATA)/sizeof(char);

    for(size_t ind = 1; ind < (this->capacity + 2) * size_converter_value ; ind++)
    {
        data_key = data_key << 3 + 1;

        data_key = data_key ^ stack_data[ind] + data_key % 3 + stack_data[ind] + stack_data[ind - 1] | stack_data[ind];
    }

    size_t secureID[3 + sizeof(cStack)] = {NULL_HASH, records_key, data_key};

    size_t ind = 0;

    for(ind = 3; ind < sizeof(cStack) / 2; ind++)
    {
        secureID[ind] = secureID[ind - 1] + secureID[ind - 1] % 5 + 2 * secureID[ind - 2] + secureID[ind - 3] % 13 ;
    }

    this->hash = secureID[ind - 1];
}

//===============================================

/*int main(void)
{
    int* ptr = (int*)calloc(2, sizeof(int));

    cStack s1(2);

    s1.stack_push(2);

    int x = 0;

    s1.stack_pop(&x);

    printf("%d\n", x);

    return 0;
} //*/
