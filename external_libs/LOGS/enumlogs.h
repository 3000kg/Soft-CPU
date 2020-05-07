#ifndef ENUMLOGS_H_INCLUDED
#define ENUMLOGS_H_INCLUDED





const char logsAmount = 10;




enum logsNumeration
{
  //0
    commonLogNum,
    textLogNum,
    printDataLogNum,
    stackLogNum,
    unittestLogNum,

  //5
    CPULogNum,
    asmLogNum,
    runLogNum,
    listLogNum,
    parserLogNum,

  //10
    enumMax
};

#endif // ENUMLOGS_H_INCLUDED
