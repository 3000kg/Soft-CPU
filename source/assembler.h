#ifndef ASSEMBLER_INCLUDED
#define ASSEMBLER_INCLUDED


#define LOG_ASM (logs.logBox + asmLogNum)

#include "../external_libs/TextStructure/textstructure.h"
#include "../external_libs/LOGS/chronology.h"
#include "../external_libs/StatusCheck/statuscheck.h"
#include "../external_libs/RecursiveDescent/rdm.h"
#include "../external_libs/CommonVerificators/verificators.h"
#include "softcpu.h"
#include <stdlib.h>
#include <stdio.h>


//Structures
    struct Mark
    {
        char* name = nullptr;
        size_t nameLength = -1;
        size_t place = -1;
    };

    typedef struct Mark mark_t;


//Consts
    const int maxBytesOnCommand   = 40;
    //const char argSepChar         = ':';
    const char cmdSep             = '\n';
    const char regSymb            = 'r';
    const char markSymb           = ':';
    const char commentSymb        = '?';



//Prototypes
    int assemble(const char* fileName, void** instruction);
    int addCommands(div_text_t* asmBuf, void** instruction, size_t* size, mark_t* marksArray);
    int byteCodeFileCreate(void** instruction, size_t size);

    #include "assembly.c"




#endif //ASSEMBLER_INCLUDED
