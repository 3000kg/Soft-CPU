#ifndef RDM_H_INCLUDED
#define RDM_H_INCLUDED

    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "../StatusCheck/statuscheck.h"
    #include "../LOGS/chronology.h"
    #include "../CommonVerificators/verificators.h"



    const char* currentSymbol       = nullptr;
    int RDMStatus                   = OK;


    typedef double rdm_data_t;


            #define LOG_RDM (logs.logBox + parserLogNum)


        //If failed once - ruining all the algorithm
            #define assertRDM(op) \
            {                                                                   \
                _dumpMacro(LOG_RDM, assertRDM);                                 \
                                                                                \
                sprintf(_comment, "Assertion checking (%s)...", #op);           \
                _writeComment(LOG_RDM, _comment);                               \
                                                                                \
                    if (!(op))                                                  \
                    {                                                           \
                            RDMStatus = FAIL;                                   \
                            _writeComment(LOG_RDM, "#ASSERTION FAILED");        \
                            _endOfFunction(LOG_RDM);                            \
                            _endOfFunction(LOG_RDM);                            \
                            return 0;                                           \
                    }                                                           \
                                                                                \
                _endOfFunction(LOG_RDM);                                        \
            }



            #define RDMstatusChk() assertRDM(RDMStatus == OK)




    char* formatParsingLine(const char* stringToAnalyze, size_t size);
    rdm_data_t mathParser(const char* line, size_t length);
    rdm_data_t getG(const char* stringToAnalyze);
    rdm_data_t getE();
    rdm_data_t getT();
    rdm_data_t getP();
    rdm_data_t getF();
    rdm_data_t getN();


    #include "descent.cpp"

#endif
