#ifndef UNITTEST_INCLUDED
#define UNITTEST_INCLUDED

#include "stdio.h"

#include "../LOGS/chronology.h"

//Setup the log;
    #define LOG_UNIT (logs.logBox + unittestLogNum)

//Unittest

#define UNITTEST(expression, op, reference, type) \
{                                                                                       \
  _dumpMacro(LOG_UNIT, UNITTEST);                                                       \
                                                                                        \
      type tempExpr = expression, tempRef = reference;                                  \
      sprintf(_comment, "\nTESTING IF (%s %s %s)\n", #expression, #op, #reference);     \
      _writeToLogBuf(LOG_UNIT, tempString);                                             \
                                                                                        \
      if (tempExpr op tempRef)                                                          \
          _writeToLogBuf(LOG_UNIT, "---PASSED\n");                                      \
      else                                                                              \
          _writeToLogBuf(LOG_UNIT, "---FAILED\n");                                      \
                                                                                        \
  _endOfFunction(LOG_UNIT);                                                             \
}

#endif //UNITTEST_INCLUDED
