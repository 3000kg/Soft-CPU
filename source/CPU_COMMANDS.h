//01.11.18
//CPU commands list
    //DEF_CMD( UNKNOWN, 255, {    _bindErr(UNKNOWN_COMMAND);          _writeToLog(LOG_CPU, "Doing function...");        })

//DEF_CMD(name, code, {function})
//don't use 1 2 and 3 bytes

//Defines
    #define db_printf printf

    #define cmdFail \
    {                                       \
        _bindErr(CMD_ASSERTION_FAIL);                  \
        _writeComment(LOG_CPU_RUN, "Aborting..."); \
        _closeLog(LOG_CPU_RUN);\
        _failReturn(LOG_CPU);\
    }


//Commands
    DEF_CMD( START, 9,
    {
        db_printf("START\n");
        _writeComment(LOG_CPU_RUN, "Start of the programm");
        _dumpFunction(LOG_CPU_RUN, _main);
        (*machine).ip += sizeof(char);

    })




    DEF_CMD( END,   10,
    {
        db_printf("END\n");
        _writeComment(LOG_CPU, "End of the soft-CPU programm...");
        _endOfFunction(LOG_CPU_RUN);
        _closeLog(LOG_CPU_RUN);
        _okReturn(LOG_CPU);
    })


//Math stack commands
    DEF_CMD( PUSH,  11,
    {
        db_printf("PUSH\n");
        (*machine).ip += sizeof(char);
        switch(*(ipCmdBytePtr))
        {
            case REG_TYPE_C :
                (*machine).ip += sizeof(char);
                if (push(&((*machine).mathStack), (*machine).registers.r[*((size_t*) ipCmdBytePtr)]) != OK)
                    cmdFail;

                (*machine).ip += sizeof(size_t);
                _writeComment(LOG_CPU_RUN, "Register pushed");
                break;


            case DATA_TYPE_C :
                (*machine).ip += sizeof(char);
                if (push(&((*machine).mathStack), *((cpu_data_t*) ipCmdBytePtr)) != OK)
                    cmdFail;

                (*machine).ip += sizeof(cpu_data_t);
                _writeComment(LOG_CPU_RUN, "Data pushed");
                break;



            case PTR_TYPE_C :
                (*machine).ip += sizeof(char);
                if (push(&((*machine).mathStack), (*machine).RAM.area[*((size_t*) ipCmdBytePtr)]) != OK)
                    cmdFail;

                (*machine).ip += sizeof(size_t);
                _writeComment(LOG_CPU_RUN, "RAM pushed");
                break;


            default :
                cmdFail;
                break;
        }
    })




    DEF_CMD( POP,   12,
        {
            db_printf("POP\n");
            (*machine).ip += sizeof(char);
            switch(*(ipCmdBytePtr))
            {
                case REG_TYPE_C :
                    (*machine).ip += sizeof(char);

                    if (pop(&((*machine).mathStack), (*machine).registers.r + *((size_t*) ipCmdBytePtr)) != OK)
                        cmdFail;

                    (*machine).ip += sizeof(size_t);
                    _writeComment(LOG_CPU_RUN, "Poped to register");
                    break;


                case PTR_TYPE_C :
                    (*machine).ip += sizeof(char);
                    if (pop(&((*machine).mathStack), (*machine).RAM.area + *((size_t*) ipCmdBytePtr)) != OK)
                        cmdFail;

                    (*machine).ip += sizeof(size_t);
                    _writeComment(LOG_CPU_RUN, "Poped to RAM");
                    break;


                default :
                    cmdFail;
                    break;
            }
        })




        DEF_CMD(MOV, 13,
        {
            db_printf("MOV\n");

        })




//Math commands
    DEF_CMD( ADD,   20,
    {
        db_printf("ADD\n");

        _writeComment(LOG_CPU_RUN, "Summarizing two numbers...");

        (*machine).ip += sizeof(char);

        cpu_data_t a = 0;
        cpu_data_t b = 0;


            if (pop(&(*machine).mathStack, &a) != OK)
                cmdFail;

            if (pop(&(*machine).mathStack, &b) != OK)
                cmdFail;

            if (push(&(*machine).mathStack, a + b) != OK)
                cmdFail;


    })





    DEF_CMD( SUB,   21,
        {
            db_printf("SUB\n");
            _writeComment(LOG_CPU_RUN, "Subtracting from head of the stack prev number");

            (*machine).ip += sizeof(char);

            cpu_data_t a = 0;
            cpu_data_t b = 0;

            if (pop(&(*machine).mathStack, &b) != OK)
                cmdFail;


            if (pop(&(*machine).mathStack, &a) != OK)
                cmdFail;

            if (push(&(*machine).mathStack, a - b) != OK)
                cmdFail;

        })





    DEF_CMD( DIV,   22,
        {
            db_printf("DIV\n");
            _writeComment(LOG_CPU_RUN, "Dividing head of the stack to prev number");

            (*machine).ip += sizeof(char);
            cpu_data_t a = 0;
            cpu_data_t b = 0;

            if (pop(&(*machine).mathStack, &b) != OK)
                cmdFail;


            if (pop(&(*machine).mathStack, &a) != OK)
                cmdFail;

            if (push(&(*machine).mathStack, a / b) != OK)
                cmdFail;

        })





    DEF_CMD( MUL,   23,
        {
            db_printf("MUL\n");
            _writeComment(LOG_CPU_RUN, "Multiplying two numbers");

            (*machine).ip += sizeof(char);
            cpu_data_t a = 0;
            cpu_data_t b = 0;

            if (pop(&(*machine).mathStack, &b) != OK)
                cmdFail;

            if (pop(&(*machine).mathStack, &a) != OK)
                cmdFail;

            if (push(&(*machine).mathStack, b * a) != OK)
                cmdFail;

        })




    DEF_CMD( POW, 24,
    {

        db_printf("POW\n");
        _writeComment(LOG_CPU_RUN, "Expanding SecondElem to FirstElem");

        (*machine).ip += sizeof(char);

        cpu_data_t a = 0;
        cpu_data_t b = 0;

        if (pop(&(*machine).mathStack, &b) != OK)
            cmdFail;

        if (pop(&(*machine).mathStack, &a) != OK)
            cmdFail;


        if (push(&(*machine).mathStack, pow(a, b)) != OK)
            cmdFail;

    })





//ip's commands:
        DEF_CMD( JMP,   101,
        {
            db_printf("JMP\n");
            _writeComment(LOG_CPU_RUN, "Jumping");

            (*machine).ip += sizeof(char);
            (*machine).ip = *((size_t*) ipCmdBytePtr);
        })





        DEF_CMD( JA,   102,
            {
                db_printf("JA\n");
                _writeComment(LOG_CPU_RUN, "JA start...");

                (*machine).ip += sizeof(char);
                cpu_data_t a = 0;
                cpu_data_t b = 0;

                if (pop(&(*machine).mathStack, &b) != OK)
                    cmdFail;

                if (pop(&(*machine).mathStack, &a) != OK)
                    cmdFail;


                if (b > a)
                {
                    (*machine).ip = *((size_t*) ipCmdBytePtr);
                    _writeComment(LOG_CPU_RUN, "head > prev; jumped");
                }

                else 
                    (*machine).ip += sizeof(size_t);

            })




        DEF_CMD( JB,   103,
        {
            db_printf("JB\n");
                _writeComment(LOG_CPU_RUN, "JB start...");

            (*machine).ip += sizeof(char);
            cpu_data_t a = 0;
            cpu_data_t b = 0;

            if (pop(&(*machine).mathStack, &b) != OK)
                cmdFail;

            if (pop(&(*machine).mathStack, &a) != OK)
                cmdFail;


            if (b < a)
            {
                (*machine).ip = *((size_t*) ipCmdBytePtr);
                _writeComment(LOG_CPU_RUN, "head < prev; jumped");
            }

            else 
                    (*machine).ip += sizeof(size_t);


        })




        DEF_CMD(CALL, 104,
        {
            db_printf("CALL\n");
            _writeComment(LOG_CPU_RUN, "Calling function...");

            (*machine).ip += sizeof(char);

            if (push(&(*machine).ipStack, (*machine).ip + sizeof(size_t)) != OK)
                cmdFail;

            (*machine).ip = *((size_t*) ipCmdBytePtr);
            _dumpFunction(LOG_CPU_RUN, unnamed_function);
        })




        DEF_CMD(RET, 105,
        {
            db_printf("RET\n");
            _writeComment(LOG_CPU_RUN, "Returning...");
            
            double ipFrStack = 0;
            if (pop(&(*machine).ipStack, &ipFrStack) != OK)
                cmdFail;

            (*machine).ip = ipFrStack;
            _endOfFunction(LOG_CPU_RUN);
        })





        DEF_CMD(PRINT, 55,
        {
            db_printf("PRINT\n");
            (*machine).ip += sizeof(char);


            switch(*(ipCmdBytePtr))
            {
                case REG_TYPE_C :
                    (*machine).ip += sizeof(char);

                    printf("%lf\n", (*machine).registers.r[*((size_t*) ipCmdBytePtr)]);
                    (*machine).ip += sizeof(size_t);
                    _writeComment(LOG_CPU_RUN, "Register printed");
                    break;

                case DATA_TYPE_C :
                    (*machine).ip += sizeof(char);
                    printf("%lf\n", *((cpu_data_t*) ipCmdBytePtr));

                    (*machine).ip += sizeof(cpu_data_t);
                    _writeComment(LOG_CPU_RUN, "Data printed");
                    break;



                case PTR_TYPE_C :
                    (*machine).ip += sizeof(char);
                    printf("%lf\n", (*machine).RAM.area[*((size_t*) ipCmdBytePtr)]);

                    (*machine).ip += sizeof(size_t);
                    _writeComment(LOG_CPU_RUN, "RAM printed");
                    break;


                default :
                    cmdFail;
                    break;
            }

        })





        DEF_CMD(SAY, 56,
        {
            db_printf("SAY\n");
            (*machine).ip += sizeof(char);
            printf("\"phrase\"\n");
            _writeComment(LOG_CPU_RUN, "Saying phrase...");
        })


#undef db_printf
