//CPU_FUNCTIONS





int runProgram(CPU_t* machine)
{
    _dumpFunction(LOG_CPU, runProgram);
    ptrCheck(machine, LOG_CPU);

      _initLog(LOG_CPU_RUN, "LOG_CPU_RUN");

      _writeComment(LOG_CPU, "Starting CPU (see another created log-file for more info)...");
      _writeComment(LOG_CPU_RUN, "Starting CPU...");

      ptrCheck((*machine).instructionsCache, LOG_CPU_RUN);
      ptrCheck((*machine).RAM.area, LOG_CPU_RUN);
      ptrCheck((*machine).registers.r, LOG_CPU_RUN);



      //do cmd:
      #define DEF_CMD(name, byte, function) \
          case byte : function; break;


      while (1)
      {
          //Getting current ip-byte;
            #define ipCmdBytePtr ((char*) (*machine).instructionsCache + (*machine).ip * sizeof(char))

            switch (*ipCmdBytePtr)
            {
                #include "CPU_COMMANDS.h"
            }

            #undef ipCmdByte
            #undef DEF_CMD
      }
}
















int loadInstuction(CPU_t* softCpu, void* instruction)
{
    _dumpFunction(LOG_CPU, loadInstuction);

    ptrCheck(softCpu, LOG_CPU);


        removeInstruction(softCpu);

        _writeComment(LOG_CPU, "Uploading code...");
        (*softCpu).instructionsCache = instruction;

    _okReturn(LOG_CPU);
}




int removeInstruction(CPU_t* softCpu)
{
    _dumpFunction(LOG_CPU, removeInstruction);

    ptrCheck(softCpu, LOG_CPU);

        if (!(*softCpu).instructionsCache)
        {
            free((*softCpu).instructionsCache);
            (*softCpu).instructionsCache = nullptr;
        }

        else
            _writeComment(LOG_CPU, "#There is no instruction!");

    _okReturn(LOG_CPU);
}



int cpuCtor(CPU_t* machine)
{
    _initLog(LOG_CPU, "LOG_CPU");
    _dumpFunction(LOG_CPU, cpuCtor);

    ptrCheck(machine, LOG_CPU);

    //Stacks

        _writeComment(LOG_CPU, "Constructing mathStack...");
        if (stackCtor(  &((*machine).mathStack)  ) != OK)
            _failReturn(LOG_CPU);



        _writeComment(LOG_CPU, "Constructing ipStack...");
        if (stackCtor(  &((*machine).ipStack)  ) != OK)
            _failReturn(LOG_CPU);

        typeidCheck(cpu_data_t, stack_data_t, LOG_CPU);
    //RAM
        (*machine).RAM.area = (cpu_data_t*) calloc(RAMsize, sizeof(cpu_data_t));
        (*machine).RAM.size = RAMsize;

        (*machine).ip = 0;
        (*machine).instructionsCache = nullptr;

    _okReturn(LOG_CPU);
}



int cpuDtor(CPU_t* machine)
{
    _dumpFunction(LOG_CPU, cpuDtor);

    ptrCheck(machine, LOG_CPU);

    //Destructing the stack
        if (stackDtor( &((*machine).mathStack)) != OK)
          _failReturn(LOG_CPU);


        if (stackDtor( &((*machine).ipStack)) != OK )
          _failReturn(LOG_CPU);

    //clearing instrCache
        if (removeInstruction(machine) != OK)
            _failReturn(LOG_CPU);

    //RAM destructing
        free((*machine).RAM.area);
        (*machine).RAM.area = nullptr;

    _okReturn(LOG_CPU);
}
