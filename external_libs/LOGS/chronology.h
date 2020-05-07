//ver 3

//02.11.18

#ifndef CHRONOLOGY_H_INCLUDED
#define CHRONOLOGY_H_INCLUDED

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "errornums.h"
    #include "enumlogs.h"
    #include "../StatusCheck/statuscheck.h"


    //Consts
        const size_t codeDepth          = 20;                       //Maximum amount of functions' calls (e.g. recursive calls)
        const size_t dumpNameLength     = 20;                       //Functions' names length
        const size_t commentLength      = 2000;                      //Comments' length
        //onst size_t dataCommentLength  = 5000;         //e.g. printStackToLog
        const char failMessage[] = "\n#\n#\n#\n---------\n|FAIL\n|In:";



    //Structures
        //dump structure is needed for monitoring functions' calls
        struct _Err
        {
            int errNo = 0;
            int errNoReturn = 0;
            char funcsTree[codeDepth][dumpNameLength] = {};
            char errName[dumpNameLength] = {};
            unsigned curFuncNo = -1;
        };

        typedef struct _Err dump_t;




        #define DEBUG_PRINT_DUMP() \
        {                                                                   \
            printf("DEBUGGING DUMP STRUCTURE:\n");                          \
            printf("1)dump.errNo = %d\n", dump.errNo);                      \
            printf("2)dump.errNoReturn = %d\n", dump.errNoReturn);          \
            printf("3)dump.curFuncNo = %d\n", dump.curFuncNo);              \
            printf("4)dump.funcsTree[][] is (from 0 to curFuncNo):\n");     \
            for (int i = 0; i <= dump.curFuncNo; i++)                       \
            {                                                               \
                for (int j = 0; j < i; j++)                                 \
                    printf("-");                                           \
                                                                            \
                printf(">%s\n", dump.funcsTree[i]);                          \
            }                                                               \
            printf("5)dump.errName: %s\n\n", dump.errName);                 \
        }



        struct _LogFile
        {
            char* path                  = nullptr;
            FILE* file                  = 0;
            int isFileClosed            = TRUE;
        };
        typedef struct _LogFile logf_t;


        struct _Log
        {
            logf_t logBox[logsAmount];
        };

        typedef struct _Log log_t;



	//Global Logs Area:
    //Logs set
        log_t logs;


    //Dump Set
        dump_t dump;

	//Consider!
        	#define LOG_COMMON (logs.logBox + commonLogNum)


        //Prototypes
      		int _writeComment(logf_t* logPtr, const char comment[]);
      		int _writeToDump(char dumpElem[], const char text[]);
      		int _closeLog(logf_t log);
      		char* _tabsGen(int count, char tab, int sepCheck);
      		int _createLogFile(logf_t* logPtr, const char path[]);
      		int _logBufAppend(logf_t* log, const char* textToAdd);
      		int _createLogFile(logf_t* logPtr, const char path[]);
      		int _initLog(logf_t* log, const char* path);
      		int _closeLog(logf_t* log);
            int _openLog(logf_t* log);



          #define _dumpMacro(logPtr, macroName) \
      	  {                                                                             \
              		if (logPtr)                                                         \
                    {                                                                   \
                        _writeToDump(dump.funcsTree[++dump.curFuncNo], #macroName);     \
                        char tempString[commentLength] = {};                            \
                        sprintf(tempString, "$__%s_CALL___", #macroName);               \
                        _writeComment(logPtr, tempString);                                \
                    }                                                                   \
                                                                                        \
          }





      	  #define _dumpFunction(logPtr, funcName) \
          if (logPtr)                                                           \
              _dumpMacro(logPtr, funcName);                                     \
          int _status = OK;                                                     \
          char _comment[commentLength] = {};





          #define _endOfFunction(logName) \
          {                                                                                 \
                if (logName && dump.funcsTree)                                              \
                {                                                                           \
                    char tempString[commentLength] = {};                                      \
                    sprintf(tempString, "@__%s_END___", dump.funcsTree[dump.curFuncNo--]);    \
                    _writeComment(logName, tempString);                                       \
                }			                                                                \
          }







      		#define _statusReturn(logName) \
      		{                              \
                if (_status == OK)         \
                    _okReturn(logName);    \
      			_failReturn(logName);      \
      		}


      		#define _okReturn(logName) \
		    {                                     \
      			assert(logName);                  \
                if (logName)                      \
      			       _endOfFunction(logName);   \
      			return OK;                        \
      		}




      		#define _failReturn(logName) \
		    {                                   \
              	assert(logName);                \
                if (logName)                    \
              	     _endOfFunction(logName);   \
              	return dump.errNoReturn;        \
      		}




            #define _bindErr(errVal) \
            {                                                      \
                assert(dump.funcsTree);                            \
      			assert(dump.errName);                              \
      			if (dump.funcsTree && dump.errName)                \
      			{                                                  \
      				_writeToDump(dump.errName, #errVal);           \
      				dump.errNo = errVal;                           \
                    dump.errNoReturn = errVal;                     \
      				_status = FAIL;                                \
      			}                                                  \
      		}



    #include "LogsFunctions.cpp"

#endif // CHRONOLOGY_H_INCLUDED
