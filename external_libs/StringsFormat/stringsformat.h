#ifndef STRINGSFORMAT_INCLUDED
#define STRINGSFORMAT_INCLUDED

#include <ctype.h>

#include "../LOGS/chronology.h"

#define LOG_STRINGSFORMAT (logs.logBox + stringsformatLogNum)


int stringToNum(char* line, int length, double* ptrToData);
int translateNum(double* number, short digitsBeforePoint );

#include "StringsFormat.cpp"

#endif	//STRINGSFORMAT_INCLUDED
