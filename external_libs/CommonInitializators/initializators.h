#ifndef INITIALIZATORS_INCLUDED
#define INITIALIZATORS_INCLUDED

#include "../CommonVerificators/verificators.h"

  #define initNum(numP, value, type, log) \
  {                                                                                             \
      assert(numP);                                                                             \
      _dumpMacro(log, initStructNum);                                                            \
                                                                                                \
          type tempValue = (value);                                                           \
          type* tempNumPtr = (numP);                                                          \
          assert(isfinite(tempValue));                                                            \
                                                                                                  \
          ptrCheck(tempNumPtr, log);                                                               \
          numCheck(tempValue, log);                                                                    \
                                                                                                  \
          typeidCheck(type, value, log);                                                          \
          typeidCheck(type, *numP, log);                                                          \
                                                                                                  \
          if (_status == OK)                                                                      \
              *tempNumPtr = tempValue;                                                            \
                                                                                                  \
    _endOfFunction(log);                                                                          \
  }


#endif //INITIALIZATORS_INCLUDED
