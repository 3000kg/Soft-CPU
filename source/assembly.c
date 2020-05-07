#ifndef ASSEMBLYCPP_INCLUDED
#define ASSEMBLYCPP_INCLUDED

//to do:
/*
1)byteCodeFileCreate - filename generation;


*/
//Macro
    #define findMatchingMark(ptr, len) \
    {                                                                                               \
        _dumpMacro(LOG_ASM, findMatchingMark);                                                      \
        char* curMarkName = ptr;                                                                    \
        size_t length = len;                                                                        \
        ptrCheck(curMarkName, LOG_ASM);                                                             \
                                                                                                    \
        size_t searchPointers = -1;                                                                 \
        size_t curLength = length;                                                                  \
        size_t cmpIDX = 0;                                                                          \
                                                                                                    \
        ptrCheck(jumpPointers, LOG_ASM);                                                            \
                                                                                                    \
            while ( jumpPointers[++searchPointers].place != -1 )                                    \
            {                                                                                           \
                if (curLength == jumpPointers[searchPointers].nameLength)                                   \
                {                                                                                               \
                    cmpIDX = 0;                                                                                         \
                    ptrCheck(jumpPointers[searchPointers].name, LOG_ASM);                                               \
                                                                                                                        \
                    while ((jumpPointers[searchPointers].name[cmpIDX] == curMarkName[cmpIDX]) && (cmpIDX < curLength))  \
                        cmpIDX++;                                                                                       \
                                                                                                                        \
                                                                                                                        \
                    if (cmpIDX == curLength)                                                                            \
                    {                                                                                                   \
                        _writeComment(LOG_ASM, "Existing mark found, adding to instruction...");                        \
                        *((size_t*) (((char*) *instruction) + ip)) = jumpPointers[searchPointers].place;                   \
                        ip += sizeof(size_t);                                                                           \
                        break;                                                                                          \
                    }                                                                                                   \
                }                                                                                                       \
            }                                                                                                           \
                                                                                                                        \
            if (jumpPointers[searchPointers].place == -1)                                       \
            {                                                                                                           \
                if (asmFlag == FALSE)                                                                                   \
                {                                                                                                       \
                    _bindErr(WRONG_MARK);                                                                                   \
                    _writeComment(LOG_ASM, "Searching matching mark...");                                                   \
                    _failReturn(LOG_ASM);\
                }                                                                                                        \
                else ip += sizeof(size_t);                                                                              \
            }                                                                                                           \
                                                                                                                        \
        _endOfFunction(LOG_ASM);                                                                                        \
    }




    #define bindMark(ptr, len) \
    {                                                                               \
        _dumpMacro(LOG_ASM, bindMark);                                              \
        char* curMarkName = ptr;                                                    \
        size_t length = len;                                                        \
        ptrCheck(curMarkName, LOG_ASM);                                             \
                                                                                    \
            jumpPointers[marksCounter].name  = curMarkName + 1;                     \
            jumpPointers[marksCounter].nameLength = length;     /*except markSymb*/ \
            jumpPointers[marksCounter].place = ip;                                  \
            marksCounter++;                                                         \
                                                                                    \
            sprintf(_comment, "Mark number: (%ld), ip is: (%ld)", marksCounter, ip);      \
            _writeComment(LOG_ASM, _comment);                                       \
                                                                                    \
        _endOfFunction(LOG_ASM);                                                    \
    }





int assemble(const char* fileName, void** instruction)
{
    _initLog(LOG_ASM, "LOG_ASM");
    _dumpFunction(LOG_ASM, assemble);
    ptrCheck(fileName, LOG_ASM);



        text_t asmText;
        if (textCtor(&asmText, fileName, "r") != OK)
            _failReturn(LOG_ASM);


        if (formatSpaces(&asmText) != OK)
            _failReturn(LOG_ASM);



        div_text_t asmLines;
        if (divTextCtor(asmText.buf, asmText.bufSize, cmdSep, &asmLines) != OK)
            _failReturn(LOG_ASM);



            size_t size = 0;
            mark_t* zeroArray = nullptr;
            //Translating asm to byte-code



            if (addCommands(&asmLines, instruction, &size, zeroArray) != OK)
                _failReturn(LOG_ASM);





            if (byteCodeFileCreate(instruction, size) != OK)
                _failReturn(LOG_ASM);




        if (divTextDtor(&asmLines) != OK)
            _failReturn(LOG_ASM);


    //Destructing text structure
        if (textDtor(&asmText) != OK)
            _failReturn(LOG_ASM);


    _okReturn(LOG_ASM);
}



int byteCodeFileCreate(void** instruction, size_t size)
{
    _dumpFunction(LOG_ASM, byteCodeFileCreate);
    _writeComment(LOG_ASM, "Byte Code file creation...");


    ptrCheck(instruction, LOG_ASM);

        FILE* file = fopen("bytecode.do", "w");
        fwrite(*instruction, 1, size, file);
        fclose(file);

/*

    text_t file;

        if (textCtor(&file, "bytecode.do", "w") != OK)
            _failReturn(LOG_ASM);





        if (textDtor(&file) != OK)
            _failReturn(LOG_ASM);
*/
    _okReturn(LOG_ASM);
}





//Defining DEF_CMD:
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    #define DEF_CMD(name, byte, operates) \
    {                                                                                                                       \
        char code = byte;   /*if sizeof(char) == 1*/                                                                        \
                                                                                                                            \
        /*string comparator*/                                                                                               \
            size_t cmpLineIDX = 0;                                                                                          \
            while ( (#name[cmpLineIDX] == currentLine[cmpLineIDX]) && (#name[cmpLineIDX] != '\0') )                         \
                cmpLineIDX++;                                                                                               \
                                                                                                                            \
            if (#name[cmpLineIDX] == '\0')                                                                                  \
            {                                                                                                               \
                sprintf(_comment, "Adding command (%s)...", #name);                                                         \
                _writeComment(LOG_ASM, _comment);                                                                           \
                                                                                                                            \
                    *(((char*) (*instruction)) + ip) = code;                                                                \
                    ip += sizeof(char);                                                                                     \
                    if (dividedLine.count > 1)                                                                              \
                    {                                                                                                       \
                        /*1) Arg is a mark ("*%s")*/                                                                        \
                            if (*dividedLine.divided[1].first == markSymb)                                                      \
                            {                                                                                                   \
                                _writeComment(LOG_ASM, "Matching mark...");                                                     \
                                findMatchingMark(dividedLine.divided[1].first + sizeof(char), dividedLine.divided[1].length - 1);          \
                                continue;                                                                                       \
                            }                                                                                                   \
                                                                                                                                \
                            size_t cmdEndIDX = 0;                                                                                               \
                            while ((dividedLine.divided[1].first[cmdEndIDX] != cmdSep) && (dividedLine.divided[1].first[cmdEndIDX] != '\0'))    \
                                cmdEndIDX++;                                                                                                    \
                                                                                                                                                \
                        /*2) Arg is a register*/                                                                                \
                            if (*dividedLine.divided[1].first == regSymb)                                                       \
                            {                                                                                                   \
                                _writeComment(LOG_ASM, "Adding register IDX to code-byte...");                                  \
                                                                                                                                \
                                size_t regIDX = mathParser(dividedLine.divided[1].first + 1, cmdEndIDX);                        \
                                if (RDMStatus != OK)\
                                {\
                                    _bindErr(INCORRECT_ASM_LINE);\
                                    _writeComment(LOG_ASM, "Checking parser result...");\
                                    _failReturn(LOG_ASM);\
                                }\
                                typeidCheck(REG_TYPE_C, char, LOG_ASM);                                                         \
                                *(((char*) *instruction) + ip) = REG_TYPE_C;                                                       \
                                ip += sizeof(char);                                                                             \
                                *((size_t*) (((char*) *instruction) + ip)) = regIDX;                                                 \
                                ip += sizeof(size_t);                                                                           \
                                continue;                                                                                       \
                            }                                                                                                   \
                                                                                                                                \
                                                                                                                                \
                        /*3) Arg is a ptr in RAM*/                                                                              \
                            if (*dividedLine.divided[1].first == '[')                                                           \
                            {                                                                                                                               \
                                _writeComment(LOG_ASM, "Adding soft-processor's RAM pointer to code-byte...");                                              \
                                size_t closeBracketIDX = 0;                                                                                                     \
                                while ((dividedLine.divided[1].first[closeBracketIDX] != cmdSep) && (dividedLine.divided[1].first[closeBracketIDX] != '\0'))    \
                                {                                                                                                                               \
                                    if (dividedLine.divided[1].first[++closeBracketIDX] == ']')                                                                \
                                        break;                                                                                                      \
                                }                                                                                                                   \
                                                                                                                                                    \
                                if (dividedLine.divided[1].first[closeBracketIDX] != ']')                                                           \
                                {                                                                                                                   \
                                    _bindErr(INCORRECT_ASM_LINE);                                                                                   \
                                    _writeComment(LOG_ASM, "Checking closing bracket...");                                                          \
                                    _failReturn(LOG_ASM);                                                                                           \
                                }                                                                                                                   \
                                                                                                                                                    \
                                size_t codePtr = mathParser(dividedLine.divided[1].first + 1, closeBracketIDX);                                     \
                                if (RDMStatus != OK)\
                                {\
                                    _bindErr(INCORRECT_ASM_LINE);\
                                    _writeComment(LOG_ASM, "Checking parser result...");\
                                    _failReturn(LOG_ASM);\
                                }\
                                typeidCheck(PTR_TYPE_C, char, LOG_ASM);                                                                  \
                                *(((char*) *instruction) + ip) = PTR_TYPE_C;                                                       \
                                ip += sizeof(char);                                                                             \
                                *((size_t*) (((char*) *instruction) + ip)) = codePtr;                                                \
                                ip += sizeof(size_t);                                                                           \
                                continue;                                                                                       \
                            }                                                                                                   \
                                                                                                                                \
                        /*protection from types missmatchings when cmd is JMP-type*/                                            \
                            if (code >= 100)                                                                                    \
                            {                                                                                                   \
                                _writeComment(LOG_ASM, "Adding ip's idx...");                                                   \
                                size_t jmpIP = mathParser(dividedLine.divided[1].first, cmdEndIDX + 1);                         \
                                if (RDMStatus != OK)\
                                {\
                                    _bindErr(INCORRECT_ASM_LINE);\
                                    _writeComment(LOG_ASM, "Checking parser result...");\
                                    _failReturn(LOG_ASM);\
                                }\
                                *((size_t*) (((char*) *instruction) + ip)) = jmpIP;                                             \
                                ip += sizeof(size_t);                                                                           \
                                continue;                                                                                       \
                            }                                                                                                   \
                                                                                                                                \
                            /*4) Arg is a mathematic expression*/                                                               \
                            {                                                                                                   \
                                _writeComment(LOG_ASM, "Adding number...");                                                     \
                                typeidCheck(cpu_data_t, rdm_data_t, LOG_ASM);                                                   \
                                cpu_data_t data = mathParser(dividedLine.divided[1].first, cmdEndIDX + 1);                      \
                                if (RDMStatus != OK)\
                                {        \
                                    _bindErr(INCORRECT_ASM_LINE);\
                                    _writeComment(LOG_ASM, "Checking parser result...");\
                                    _failReturn(LOG_ASM);\
                                }\
                                                                                                                                \
                                typeidCheck(DATA_TYPE_C, char, LOG_ASM);                                                        \
                                *(((char*) *instruction) + ip) = DATA_TYPE_C;                                                   \
                                ip += sizeof(char);                                                                             \
                                *((cpu_data_t*) (((char*) *instruction) + ip)) = data;                                          \
                                ip += sizeof(cpu_data_t);                                                                       \
                            }                                                                                                   \
                                                                                                                                \
                    }                                                                                                       \
                continue;                                                                                                   \
            }                                                                                                               \
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int addCommands(div_text_t* asmBuf, void** instruction, size_t* size, mark_t* marksArray)
{

    assert(asmBuf);
    assert(instruction);
    _dumpFunction(LOG_ASM, addCommands);


        *instruction  = calloc( (*asmBuf).count, maxBytesOnCommand );


        int asmFlag = FALSE;
        mark_t* jumpPointers;


        if (marksArray == nullptr)
        {
            jumpPointers = (mark_t*) calloc( (*asmBuf).count, sizeof(mark_t) );
            for (int i = 0; i < (*asmBuf).count; i++)
            {
                jumpPointers[i].nameLength  = -1;
                jumpPointers[i].place       = -1;
            }

            asmFlag = TRUE;
        }

        else jumpPointers = marksArray;


        ptrCheck(*instruction, LOG_ASM);
        ptrCheck(jumpPointers, LOG_ASM);


            size_t asmLinesCounter  = 0;
            size_t marksCounter     = 0;
            size_t ip               = 0;

            for ( asmLinesCounter = 0;    asmLinesCounter < (*asmBuf).count;     asmLinesCounter++ )
            {
                //Considering the current line:
                char* currentLine = (*asmBuf).divided[asmLinesCounter].first;
                ptrCheck(currentLine, LOG_ASM);


                if (currentLine[0] == commentSymb) //check if it isn't comment;
                    continue;


                //mark's format doesn't allow use of ' '
                div_text_t dividedLine;
                divTextCtor(currentLine, (*asmBuf).divided[asmLinesCounter].length, ' ', &dividedLine);


                if (currentLine[0] == markSymb) //check if it is mark;
                {
                    _writeComment(LOG_ASM, "Mark found!");
                    bindMark(currentLine, dividedLine.divided[0].length - 1); //except markSymb;
                    divTextDtor(&dividedLine);
                    continue;
                }


                    #include "CPU_COMMANDS.h"
                }


        *size = ip;

        if (asmFlag == TRUE)
        {
            if (addCommands(asmBuf, instruction, size, jumpPointers) != OK)
                _failReturn(LOG_ASM);
        }

        else
            free(jumpPointers);
        //*instruction = realloc(*instruction, ip + 1);



    _okReturn(LOG_ASM);
}



//Undefining local macroses
#undef DEF_CMD
#undef bindMark
#undef findMatchingMark

#endif//ASSEMBLYCPP_INCLUDED
