//02.11.18
//ver 3

//CONSTRUCTOR
int stackCtor(stack_t* stackP)
{
    _initLog(LOG_STACK, "LOG_STACK");
    _dumpFunction(LOG_STACK, stackCtor);

    //Const checking:
    //----------------------------------------------------------------------------------------------------
    // 1)                                                                                               //
        typeidCheck(defaultStackLen, size_t, LOG_STACK);                                                //                                                                                      //
                                                                                                        //
    // 2)                                                                                               //
        typeidCheck(expBufDefault, size_t, LOG_STACK);                                                  //
                                                                                                        //
        if (expBufDefault == 0)                                                                         //
            _bindErr(BAD_DEFAULT_LEN);                                                                  //
                                                                                                        //
        _writeComment(LOG_STACK, "expBufDefault checking...");                                            //
                                                                                                                //
    // 3)                                                                                               //
        typeidCheck(STACK_MULTIPLIER, short, LOG_STACK);                                                //
                                                                                                        //
        if (STACK_MULTIPLIER == 0)                                                                     //
            _bindErr(BAD_MULTIPLIER);                                                                   //
                                                                                                        //
        _writeComment(LOG_STACK, "Multiplier checking...");                                               //
                                                                                                        //
    // 4)                                                                                               //
        typeidCheck(lStackWall, stack_data_t, LOG_STACK);                                                     //
        typeidCheck(rStackWall, stack_data_t, LOG_STACK);                                                     //
        typeidCheck(lNumsWall, size_t, LOG_STACK);                                                      //
        typeidCheck(rNumsWall, size_t, LOG_STACK);                                                      //
                                                                                                        //
    // 5)                                                                                               //
        poisonCheck(stackPOISON, stack_data_t, LOG_STACK);                                                           //
    //---------------------------------------------------------------------------------------------------


    if (_status != OK)
    {
        _writeComment(LOG_STACK, "#CONSIDER!\nSTRUCTURE_CONSTS_FAILURE");
        _failReturn(LOG_STACK);
    }

    //Starting an initialization
        //Building the stack data area:
        //--------------------------------------------------------------------------------------------------------------------
            (*stackP).data = ((stack_data_t*) calloc(defaultStackLen + 2, sizeof(stack_data_t)));                           //
                                                                                                                            //
            ptrCheck((*stackP).data, LOG_STACK);                                                                            //
            (*stackP).data[0] = lStackWall;                                                                                 //
            (*stackP).data[defaultStackLen + 1] = rStackWall;                                                               //
            (*stackP).data++; //to skip the left wall;                                                                      //
        //-------------------------------------------------------------------------------------------------------------------


        //Building the area of structure's numbers:
        //--------------------------------------------------------------------------------------------
            (*stackP).structNumsArea = (size_t*) calloc(5, sizeof(size_t));                         //
                                                                                                    //
            ptrCheck((*stackP).structNumsArea, LOG_STACK);                                           //                                                                      //
                                                                                                    //
            (*stackP).structNumsArea[0] = lNumsWall;                                                //
            (*stackP).sizePtr           = (*stackP).structNumsArea + 1;                             //
            (*stackP).capacityPtr       = (*stackP).structNumsArea + 2;                             //
            (*stackP).expandBufToPtr    = (*stackP).structNumsArea + 3;                             //
            (*stackP).structNumsArea[4] = rNumsWall;                                                //
                                                                                                    //
            initNum((*stackP).sizePtr, (size_t) 0, size_t, LOG_STACK);                              //
                                                                                                    //
            initNum((*stackP).capacityPtr, defaultStackLen, size_t, LOG_STACK);                     //
                                                                                                    //
            initNum((*stackP).expandBufToPtr, expBufDefault, size_t, LOG_STACK);                    //
        //--------------------------------------------------------------------------------------------
        //End of building the area of structure's numbers


    if (_status != OK) //_status changing by initNum
    {
        _writeComment(LOG_STACK, "#_CONSIDER!\nNUMBERS_INITIALIZATION_FAILURE");
        _failReturn(LOG_STACK);
    }

    //Stack initialization:
        //----------------------------------------------------
            size_t i = 0;                                   //
            for (i = 0; i < *(*stackP).capacityPtr; i++)    //
                *((*stackP).data + i) = stackPOISON;        //
        //---------------------------------------------------


    _writeComment(LOG_STACK, "Stack successfully created:");

    //printStackToLog(LOG_STACK, stackP, "\nStack after the construction:");

    _okReturn(LOG_STACK);
}


//DESTRUCTOR
int stackDtor(stack_t* stackP)
{
    _dumpFunction(LOG_STACK, stackDtor);

    //Structure check:
    ptrCheck(stackP, LOG_STACK);


    printStackToLog(LOG_STACK, stackP, "\nStack before the destruction:");

    //Freeing allocated data
    //-------------------------------------------------------------------//
        free(--(*stackP).data);                                          //
        _writeComment(LOG_STACK, "Freeing stack data area...");     //
    //-------------------------------------------------------------------//

    //Freeing allocated memory
    //--------------------------------------//
        free((*stackP).structNumsArea);     //
        (*stackP).data = 0;                 //
        (*stackP).structNumsArea = 0;       //
    //--------------------------------------//


    _writeComment(LOG_STACK, "Stack successfully destructed");

    _endOfFunction(LOG_STACK);
    _closeLog(LOG_STACK);
    return OK;
}



//MAIN COMMANDS (push(), pop())
int push(stack_t* stackP, stack_data_t elem)
{
    _dumpFunction(LOG_STACK, push);

    assert(stackP);
    assert(isfinite(elem));
    numCheck(elem, LOG_STACK);

    //Stack condition checking
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);


    //Checking free space and adding memory if necessary
    //----------------------------------------------------------//
    if (*(*stackP).sizePtr == *(*stackP).capacityPtr)           //
	{							//
            if (stackAddMem(stackP) != OK)                         //
                _failReturn(LOG_STACK);                         //
	//Stack condition checking				//
            if (stackOK(stackP) != OK)			//
        	_failReturn(LOG_STACK);			        //
	}							//
    //----------------------------------------------------------//


    _writeComment(LOG_STACK, "Adding element...");
    //Adding new element and increasing the size
    //--------------------------------------------------//
        (*stackP).data[(*(*stackP).sizePtr)++] = elem;    //
    //--------------------------------------------------//
    printStackToLog(LOG_STACK, stackP, "\nStack after pushing:");


    //Stack condition checking
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    _okReturn(LOG_STACK);
}


int pop(stack_t* stackP, stack_data_t* place)
{
    _dumpFunction(LOG_STACK, pop);

    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);


    //Checking if there are elements to pop:
    if (*(*stackP).sizePtr == 0)
    {
        _bindErr(STACK_UNDERFLOW);
        _writeComment(LOG_STACK, "Popping element...");

        _writeComment(LOG_STACK, "#STACK UNDERFLOW");
        _failReturn(LOG_STACK);
    }

    //Checking the place for the popping element:
    ptrCheck(place, LOG_STACK);

    //Popping the element, replacing it with stackPOISON constant and decreasing the size:
    //----------------------------------------------//
    *place = (*stackP).data[--(*(*stackP).sizePtr)];//
                                                    //
    (*stackP).data[*(*stackP).sizePtr] = stackPOISON;    //
    //----------------------------------------------//
    printStackToLog(LOG_STACK, stackP, "\nStack after popping:");

    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    //Removing unused memory:
    if ((*(*stackP).sizePtr > expBufDefault) and (STACK_MULTIPLIER * STACK_MULTIPLIER * *(*stackP).sizePtr <= 2 * *(*stackP).capacityPtr))
        if (stackRemoveMem(stackP) != OK)
            _failReturn(LOG_STACK);


    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    _okReturn(LOG_STACK);
}

//SECONDARY FUNCTIONS
int stackAddMem(stack_t* stackP)
{
    _dumpFunction(LOG_STACK, addMem);

    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    printStackToLog(LOG_STACK, stackP, "\nStack before addMem:");

    //Allocating necessary amount of memory
    //------------------------------------------------------------------------------------------------------//
    void* tempPtr = 0;                                                                                      //
    tempPtr = realloc((void*) ((*stackP).data - 1), (*(*stackP).expandBufToPtr + 2) * sizeof(stack_data_t));      //
    if (tempPtr == 0)                                                                                       //
    {                                                                                                       //
        _bindErr(ADD_MEM_FAIL);                                                                             //
        _writeComment(LOG_STACK, "Reallocating the stack...");                                         //
        _failReturn(LOG_STACK);                                                                             //
    }                                                                                                       //
    _writeComment(LOG_STACK, "Reallocating the stack...");                                             //
                                                                                                            //
    (*stackP).data = (stack_data_t*) tempPtr;                                                                     //
    (*stackP).data[0] = lStackWall;                                                                          //
    *(*stackP).capacityPtr = *(*stackP).expandBufToPtr;                                                     //
    (*stackP).data[*(*stackP).capacityPtr + 1] = rStackWall;                                                 //
    (*stackP).data++;                                                                                       //
    *(*stackP).expandBufToPtr *= STACK_MULTIPLIER;                                                                //
    //------------------------------------------------------------------------------------------------------//


    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    //Clearing new allocated area:
    //------------------------------------------------------------------//
        size_t i = 0;                                                   //
        for (i = *(*stackP).sizePtr; i < *(*stackP).capacityPtr; i++)   //
            (*stackP).data[i] = stackPOISON;                            //
    //------------------------------------------------------------------//

    printStackToLog(LOG_STACK, stackP, "\nStack after addMem:");

    //Stack condition checking:
        if (stackOK(stackP) != OK)
                _failReturn(LOG_STACK);

    _writeComment(LOG_STACK, "Reallocating finished;");

    _okReturn(LOG_STACK);
}


int stackRemoveMem(stack_t* stackP)
{
    _dumpFunction(LOG_STACK, stackRemoveMem);

    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    //Checking if there are enough free space:
        if (!(*(*stackP).sizePtr > expBufDefault) and (STACK_MULTIPLIER * STACK_MULTIPLIER * *(*stackP).sizePtr <= 2 * *(*stackP).capacityPtr))
        {
            _bindErr(WRONG_REMOVEMEM_CALL);
            _writeComment(LOG_STACK, "Calling removeMem");
            _failReturn(LOG_STACK);
        }
        _writeComment(LOG_STACK, "Calling removeMem...");


    printStackToLog(LOG_STACK, stackP, "\nStack before removeMem:");

    //Deleting free space:
    //----------------------------------------------------------------------------------------------------------------------//
        void* tempPtr = 0;                                                                                                  //
        tempPtr = realloc((void*) ((*stackP).data - 1), ( *(*stackP).capacityPtr / STACK_MULTIPLIER + 2) * sizeof(stack_data_t) );      //
        if (tempPtr == 0)                                                                                                   //
        {                                                                                                                   //
            _bindErr(REMOVE_MEM_FAIL);                                                                                      //
            _writeComment(LOG_STACK, "Removing memory...");                                                                //
            _failReturn(LOG_STACK);                                                                                         //
        }                                                                                                                   //
         _writeComment(LOG_STACK, "Removing memory...");                                                                   //
                                                                                                                            //
        _writeComment(LOG_STACK, "Changing stack's parameters...");                                                        //
                                                                                                                            //
        (*stackP).data = (stack_data_t*) tempPtr;                                                                                 //
        *(*stackP).expandBufToPtr = *(*stackP).capacityPtr;                                                                 //
        (*stackP).data[0] = lStackWall;                                                                                      //
        *(*stackP).capacityPtr /= STACK_MULTIPLIER;                                                                               //
        (*stackP).data[*(*stackP).capacityPtr + 1] = rStackWall;                                                             //
        (*stackP).data++;                                                                                                   //
    //----------------------------------------------------------------------------------------------------------------------//

    printStackToLog(LOG_STACK, stackP, "\nStack after removeMem:");

    //Stack condition checking:
        if (stackOK(stackP) != OK)
            _failReturn(LOG_STACK);

    _okReturn(LOG_STACK);
}



//STACK CHECKING
int stackOK(stack_t* stackP)
{
    _dumpFunction(LOG_STACK, stackOK);


        ptrCheck(stackP, LOG_STACK);
        ptrCheck((*stackP).data, LOG_STACK);


    //Checking if there were unauthorized data changes:
    //----------------------------------------------------------------------------------//
        if ((*stackP).data != nullptr )                                          //
        {                                                                               //
            //Left Wall check                                                           //
            if ( *((*stackP).data - 1) != lStackWall )                               //
            {                                                                           //
                printStackToLog(LOG_STACK, stackP, "\nConsider on the left wall:");     //
                _bindErr(LEFT_WALL_BROKEN);                                        //
            }                                                                           //
            _writeComment(LOG_STACK, "Left Data Wall checking...");                       //
                                                                                        //
            //Right Wall check				                                //
            if ( (*stackP).data[*(*stackP).capacityPtr] != rStackWall )   	        //
            {                                                                           //
                printStackToLog(LOG_STACK, stackP, "\nConsider on the right wall:");    //
                _bindErr(RIGHT_WALL_BROKEN);                                       //
            }                                                                           //
            _writeComment(LOG_STACK, "Right Data Wall checking...");                      //
        }                                                                               //
    //----------------------------------------------------------------------------------//


    //Checking stack parameters area:
    //-------------------------------------------------------//
        if (stackStructNumsCheck(stackP, 1, 1, 1) != OK)   //
            _status = FAIL;                                  //
    //-------------------------------------------------------//


    //Checking if stack looks normally (size < capacity e.g.)
    //--------------------------------------------------------------------------//
        size_t capacity = 0, size = 0, expandBufTo = 0;                         //
        capacity = *(*stackP).capacityPtr;                                      //
        size = *(*stackP).sizePtr;                                              //
        expandBufTo = *(*stackP).expandBufToPtr;                                //
                                                                                //
        if (size > capacity)                                                    //
        {                                                                       //
            printStackToLog(LOG_STACK, stackP, "\nSize over Capacity:");        //
            _bindErr(SIZE_OVER_CAPACITY)//;                                       //
        }
        _writeComment(LOG_STACK, "Capacity and size checking...");         //
                                                                                //
        if (capacity >= expandBufTo)                                            //
        {
            printStackToLog(LOG_STACK, stackP, "\nCapacity over ExpTo (expandBufTo = capacity * STACK_MULTIPLIER):");
            _bindErr(CAP_OVER_EXPTO)//;                                           //
        }
         _writeComment(LOG_STACK, "Capacity and ExpandBufTo checking..."); //
    //--------------------------------------------------------------------------//


    _statusReturn(LOG_STACK);
}



int stackStructNumsCheck(stack_t* stackP, bool capCheck, bool sizeCheck, bool expToCheck)
{
    _dumpFunction(LOG_STACK, structNumsCheck);

    //Checking structure PTR:
    ptrCheck(stackP, LOG_STACK);

    //Checking structure's numbers' area
    ptrCheck((*stackP).structNumsArea, LOG_STACK);


    //Checking if there were unexpected numbers' area changes:
    //------------------------------------------------------------------------------//
        if ((*stackP).structNumsArea[0] != lStackWall)                              //
        {                                                                           //
            _bindErr(LEFT_WALL_BROKEN);                                             //
            _writeComment(LOG_STACK, "NumsArea's left wall checking...");           //
            _failReturn(LOG_STACK);                                                 //
        }                                                                           //
        _writeComment(LOG_STACK, "NumsArea's left wall checking...");               //
                                                                                    //
                                                                                    //
        if ((*stackP).structNumsArea[4] != rStackWall)                              //
        {                                                                           //
            _bindErr(RIGHT_WALL_BROKEN);                                            //
            _writeComment(LOG_STACK, "NumsArea's right wall checking...");          //
            _failReturn(LOG_STACK);                                                 //
        }                                                                           //
        _writeComment(LOG_STACK, "NumsArea's right wall checking...");              //
    //------------------------------------------------------------------------------//

    //Check (if it needs) content for NAN:
    //--------------------------------------------------------------------------//
        //1) Capacity                                                           //
        if (capCheck == TRUE)                                                   //
            numCheck(*(*stackP).capacityPtr, LOG_STACK);                       //
                                                                                //
        //2) Size                                                               //
        if (sizeCheck == TRUE)                                                  //
            numCheck(*(*stackP).sizePtr, LOG_STACK);                           //
                                                                                //
        //3) ExpandBufTo                                                        //
        if (expToCheck == TRUE)                                                 //
            numCheck(*(*stackP).expandBufToPtr, LOG_STACK);                     //
    //--------------------------------------------------------------------------//

    _statusReturn(LOG_STACK);
}




int printStackToLog(logf_t* log, stack_t*  stackP, const char* comment)
{
    assert(log);
    _dumpFunction(log, printStackToLog);

    assert(stackP);
    ptrCheck(stackP, LOG_STACK);

    char* stackInLine = nullptr;

    if (sprintStack(stackP, &stackInLine, comment) != OK)
    {
        _writeComment(log, "#CONSIDER!: CANT PRINT STACK");
        _failReturn(log);
    }

    _writeComment(log, stackInLine);
    //_writeComment(log, stackInLine);

    free(stackInLine);
    _okReturn(log);
}





//OUTPUT____________________________________________________________________________
int sprintStack(stack_t* stackP, char** lineWithStack, const char* comment)
{
  assert(stackP);
  assert(lineWithStack);
  _initLog(LOG_PRINTDATA, "LOG_PRINTDATA");
  _dumpFunction(LOG_STACK, sprintStack);


  //Checks:
    //Nums:
        if (stackStructNumsCheck(stackP, TRUE, TRUE, FALSE) != OK)
        {
            _writeComment(LOG_STACK, "#STRUCT_NUMS_ERROR");
            _failReturn(LOG_STACK);
        }

    //Data area:
        ptrCheck(stackP, LOG_STACK);
        ptrCheck((*stackP).data, LOG_STACK);


    //Input line size allocation
          *lineWithStack = (char*) calloc(printStackLength, sizeof(char));
          char elemLine[20] = {};

          if (!(*lineWithStack))
              _bindErr(CANT_PRINT_STACK)//;

          else
          {
          //----------------------------------------------------------------------------------------------//
              sprintf(*lineWithStack, "\n%s", comment);
              sprintf(*lineWithStack, "%s%s", *lineWithStack, topOfStack);
              sprintf(*lineWithStack, "%s/THE STACK   (%p)                       \\\n", *lineWithStack, stackP);                                                     //
              sprintf(*lineWithStack, "%s|--size = %ld\n|--capacity = %ld\n", *lineWithStack, *(*stackP).sizePtr, *(*stackP).capacityPtr);   //
              size_t i = 0;                                                                               //
              int wallChar = 0;

          //First Wall:
                sprintf(*lineWithStack, "%s|----------------------------------------------------\n", *lineWithStack);
                sprintf(*lineWithStack, "%s|     LEFT (FIRST) WALL:            ", *lineWithStack);
                print_data_t((*stackP).data[-1], elemLine);
                wallChar = (int) (*stackP).data[-1];
                sprintf(*lineWithStack, "%s%c\n", *lineWithStack, wallChar);
                sprintf(*lineWithStack, "%s|----------------------------------------------------\n| (VISIBLE AREA)\n|\n", *lineWithStack);


          //Data Area:
              for (i = 0; i < *(*stackP).sizePtr; i++)                                                    //
              {                                                                                           //
                  sprintf(*lineWithStack, "%s|     #_ELEM_N %-3.ld IS:              ", *lineWithStack, i);  //
                                                                                                          //
                  //Printing Element:
                      print_data_t((*stackP).data[i], elemLine);                                          //
                      sprintf(*lineWithStack, "%s%s\n", *lineWithStack, elemLine);                        //
                  //status changing by macro print_data_t()                                               //
                      if (_status != OK)                                                                 //
                          _writeComment(LOG_STACK, "#CONSIDER! CANNOT PRINT ELEM");                      //
              }                                                                                           //
                                                                                                          //
              sprintf(*lineWithStack, "%s|----------------------------------------------------\n| (INVISIBLE AREA)\n|\n", *lineWithStack);

          //Unranged area:
              for (i = *(*stackP).sizePtr; i < *(*stackP).capacityPtr; i++)                               //
              {                                                                                           //
                  sprintf(*lineWithStack, "%s|     ##_UNRANGED_N %-3.ld ELEM_IS:   ", *lineWithStack, i);                                    //
                                                                                                          //
                  //Printing Element:                                                                     //
                    print_data_t((*stackP).data[i], elemLine);                                                                //
                    sprintf(*lineWithStack, "%s%s\n", *lineWithStack, elemLine);                                                   //
                  //status changing by macro print_data_t()                                               //
                      if (_status != OK)                                                                 //
                          _writeComment(LOG_STACK, "#CONSIDER! CANNOT PRINT ELEM");                      //
              }                                                                                           //

          //Second Wall:
            sprintf(*lineWithStack, "%s|----------------------------------------------------\n", *lineWithStack);
            sprintf(*lineWithStack, "%s|     RIGHT (SECOND) WALL:          ", *lineWithStack);
            //print_data_t((*stackP).data[i], elemLine); //i increased by last iteration;
            wallChar = (int) (*stackP).data[i];
            sprintf(*lineWithStack, "%s%c\n", *lineWithStack, wallChar);
            sprintf(*lineWithStack, "%s|----------------------------------------------------\n", *lineWithStack);


            sprintf(*lineWithStack, "%s%s", *lineWithStack, botOfStack);
          }
    //----------------------------------------------------------------------------------------------//



    _writeComment(LOG_STACK, "Checking space to create stack output buffer...");


    _closeLog(LOG_PRINTDATA);


    _statusReturn(LOG_STACK);
}
