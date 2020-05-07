#ifndef SOFTCPU_INCLUDED
#define SOFTCPU_INCLUDED

// git support was realized

    #include <math.h>
    #include "../external_libs/LOGS/chronology.h"
    #include "../external_libs/Stack/stackstructure.h"
    #include "assembler.h"


    #define LOG_CPU (logs.logBox + CPULogNum)
    #define LOG_CPU_RUN (logs.logBox + runLogNum)

    typedef double cpu_data_t;


    //Consts
        const size_t RAMsize = 5000;
        const size_t defaultRegistersAmount = 11;



    //Flags
        const char REG_TYPE_C   = 1;
        const char PTR_TYPE_C   = 2;
        const char DATA_TYPE_C  = 3;


    struct Registers
    {
        cpu_data_t r[defaultRegistersAmount]    = {};
        const size_t amount                     = defaultRegistersAmount;
    };

    typedef struct Registers REG_t;


    struct CPU_RAM
    {
        cpu_data_t* area = nullptr;
        size_t size = 0;
    };

    typedef struct CPU_RAM RAM_t;


    struct SoftCPU
    {
        stack_t mathStack;
        stack_t ipStack;

        void* instructionsCache = nullptr;
        size_t ip = 0;

        RAM_t RAM;

        REG_t registers;
    };

    typedef struct SoftCPU  CPU_t;


    //Prototypes
        int runProgram(CPU_t* machine);
        int loadInstuction(CPU_t* softCpu, void* instruction);
        int removeInstruction(CPU_t* softCpu);
        int cpuCtor(CPU_t* procPtr);
        int cpuDtor(CPU_t* procPtr);

    #include "CPU.c"

#endif
