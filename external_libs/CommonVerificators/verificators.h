#ifndef VERIFICATORS_INCLUDED
#define VERIFICATORS_INCLUDED

#include <typeinfo>
#include <cmath>

#define typeidCheck(val1, val2, log) \
{                                                 \
  _dumpMacro(log, typeidCheck);                   \
                                                  \
    if (typeid(val1) != typeid(val2))             \
        _bindErr(TYPE_MISSMATCH);                 \
                                                                                        \
    sprintf(_comment, "Checking typeid match of (%s) and (%s)...", #val1, #val2);       \
    _writeComment(log, _comment);                                                         \
                                                   \
  _endOfFunction(log);                             \
}


#define assertionCheck(assertion, log) \
{                                                                       \
    _dumpMacro(log, assertionCheck);                                    \
                                                                        \
    if (!assertion)                                                     \
        _bindErr(ASSERTION_FAIL);                                       \
                                                                        \
    sprintf(_comment, "Assertion (%s) checking...", #assertion);        \
    _writeComment(log, _comment);                                       \
                                                                        \
    if (_status == FAIL)                                                \
    {                                                               \
            _writeComment(log, "Exiting...");                       \
            _endOfFunction(log);                                    \
            _failReturn(log);                                       \
    }                                                               \
                                                                    \
    _endOfFunction(log);                                            \
}




#define ptrCheck(ptr, log) \
{                                                                       \
    _dumpMacro(log, ptrCheck);                                          \
                                                                        \
        if (ptr == nullptr)                                             \
                _bindErr(DEAD_POINTER);                                 \
                                                                        \
        sprintf(_comment, "Pointer (%s) checking...", #ptr);            \
        _writeComment(log, _comment);                                   \
                                                                        \
        if (_status == FAIL)                                            \
        {                                                               \
                _writeComment(log, "Exiting...");                       \
                _endOfFunction(log);                                    \
                _failReturn(log);                                       \
        }                                                               \
                                                                        \
    _endOfFunction(log);                                                \
}



#define numCheck(num, log) \
{                                                                       \
    _dumpMacro(log, numCheck);                                          \
                                                                        \
        if (!std::isfinite(num))                                        \
                _bindErr(NOT_A_NUMBER);                                 \
                                                                        \
        sprintf(_comment, "Number (%s) checking...", #num);             \
        _writeComment(log, _comment);                                   \
                                                                        \
        if (_status == FAIL)                                            \
        {                                                               \
                _writeComment(log, "Exiting...");                       \
                _endOfFunction(log);                                    \
                _failReturn(log);                                       \
        }                                                               \
                                                                        \
    _endOfFunction(log);                                                \
}


#define poisonCheck(poison, type, log) \
{                                               \
    _dumpMacro(log, poisonCheck);               \
                                                \
    /*Checking the POISON constant:*/           \
        if (!isfinite(poison))                  \
            _bindErr(NAN_POISON);		        \
                                                \
        _writeComment(log, "Poison checking..."); \
                                                \
        typeidCheck(poison, type, log);         \
                                                \
    _endOfFunction(log);                        \
}


#endif //VERIFICATORS_INCLUDED
