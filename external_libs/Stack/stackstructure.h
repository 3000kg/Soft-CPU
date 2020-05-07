#ifndef STACKSTRUCTURE_H_INCLUDED
#define STACKSTRUCTURE_H_INCLUDED

//Includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <math.h>


    //Log setup
        //Dump
    #include "../LOGS/chronology.h"
    extern dump_t dump;
    extern log_t logs;

    ////!!!!
    #define LOG_STACK (logs.logBox + stackLogNum)
     ////!!!!

    //libs
    #include "../StatusCheck/statuscheck.h"                 //Status check consts
    #include "../PrintData/printdata.h"                     //PrintData
    #include "../_UNITTEST/unittest.h"                      //Unittest
    #include "../CommonVerificators/verificators.h"
    #include "../CommonInitializators/initializators.h"

//STACK DATA TYPE
    typedef double stack_data_t;

//Structure
    struct Stack
    {
        size_t* structNumsArea = 0;
        stack_data_t* data = 0;
        size_t* capacityPtr = 0;
        size_t* sizePtr = 0;
        size_t* expandBufToPtr = 0;
    };

    typedef struct Stack stack_t;


//STACK CONSTS
    const short STACK_MULTIPLIER    = 3;
    const size_t defaultStackLen    = 2;
    const size_t expBufDefault      = 10;
    const stack_data_t lStackWall   = 0x4C;
    const stack_data_t rStackWall   = 0x52;
    const size_t lNumsWall          = 0x4C; //ASCII 'L'
    const size_t rNumsWall          = 0x52; //ASCII 'R'
    const double stackPOISON        = -0.000666;
    const char topOfStack[]         = "\n ___________________________________________________\n";
    const char botOfStack[]         = "| END OF THE STACK\n\\___________________________________________________/\n";
    const int printStackLineLen     = 200;
    const int printStackLength      = 10000;


//Prototypes
    //stack initialization:
        int stackCtor(stack_t* stackP);
        int stackDtor(stack_t* stackP);

    //stack operates:
        int push(stack_t* stackP, stack_data_t elem);
        int pop(stack_t* stackP, stack_data_t* elemP);

    //secondary functions:
        int stackRemoveMem(stack_t* stackP);
        int stackAddMem(stack_t* stackP);

    //stack checks:
        int stackOK(stack_t* stackP);
        int stackStructNumsCheck(stack_t* stackP, bool capCheck, bool sizeCheck, bool expToCheck);

    //output:
        int sprintStack(stack_t* stackP, char** lineWithStack, const char* comment);
        int printStackToLog(logf_t* log, stack_t*, const char* comment);

//Defines



    #include "StackStructure.cpp"

#endif // STACKSTRUCTURE_H_INCLUDED
