#ifndef TEXTSTRUCTURE_DEFINED
#define TEXTSTRUCTURE_DEFINED

    #include "../StatusCheck/statuscheck.h"
    #include "../LOGS/chronology.h"
    #include "../CommonVerificators/verificators.h"
    //const size_t defaultTextCapacity = 5000;


    struct Text
    {
        FILE* file                  = 0;
        char* buf                   = 0;
        size_t bufSize              = 0;
        size_t bufCap               = 0;
        int isFileClosed            = TRUE;
    };

    typedef struct Text text_t;



    struct ElementaryText
    {
        char* first = nullptr;
        size_t length = 0;
    };

    typedef struct ElementaryText elem_text_t;


    struct DividedText
    {
        elem_text_t* divided = nullptr;
        size_t count = 0;
    };

    typedef struct DividedText div_text_t;




    //Globals
        extern struct _Err dump;
        extern log_t logs;


    //Log setup
      ////!!!!
        #define LOG_TEXT (logs.logBox + textLogNum)
      ////!!!!Dtor

    //Prototypes
    int textCtor(text_t* textStruct, const char* fileName, const char* rules);
    int openFile(text_t* text, const char* path, const char* rules);
    int readFile(text_t* textSruct);
    int textDtor(text_t* textStruct);
    int closeText(text_t* text);
    int fileIsClosed(text_t* text);
    int textBufAppend(text_t* textStructure, const char* textToAdd);
    int textPtrCheck(text_t* textSructure);
    int getSizeOfFile(text_t* textStruct, size_t* sizeOfFile);
    int divTextCtor(char* textBuf, size_t bufLength, char div, div_text_t* result);
    int divTextDtor(div_text_t*);
    int printDivText(div_text_t* text);
    int formatSpaces(text_t* text);
    size_t countChar(char* buf, char ch);

	#include "TextStructure.cpp"

#endif // TEXTSTRUCTURE_DEFINED
