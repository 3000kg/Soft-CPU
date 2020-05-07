

int stringToNum(char* line, int length, double* ptrToData) 
{
    _dumpFunction(LOG_COMMON, stringToNum);


        static double tempAns = 0;
        double tempNum        = 0;
        short dotFlag = FALSE, isEnd = TRUE, digitsBeforePoint  = 0;


        while (length-- > 0 )
        {
            /* Check for point  */
            if (line[length] != '.')
            {

                if (line[length] == '+')
                {
		    _writeToLog(LOG_COMMON, "#found new element!");
		    _writeToLog(LOG_COMMON, "Adding new element...");

                    translateNum(&tempNum, digitsBeforePoint);

                    tempAns += tempNum;
                    stringToNum(line, length, ptrToData);
                    isEnd = FALSE;
                    break;
                }

                if (line[length] == '-')
                {
		    _writeToLog(LOG_COMMON, "#found new element!");
		    _writeToLog(LOG_COMMON, "Subtracting new element...");

                    translateNum(&tempNum, digitsBeforePoint);

                    tempAns -= tempNum;
                    stringToNum(line, length, ptrToData);
                    isEnd = FALSE;
                    break;
                }

                /*Check if char is digital*/
                if (  isdigit(line[length])  )
                {
                    if (dotFlag == TRUE)
                        digitsBeforePoint++;

                    tempNum /= 10;
                    tempNum += line[length] - '0';
                }
                else if (line[length] != ' ')
                    _writeToLog(LOG_COMMON, "#SYMBOL ISN'T DIGIT!");
            }

            else
            {
                if (dotFlag == TRUE)
                {
                    _writeToLog(LOG_COMMON, "#SECOND_DOT!");
                    break;
                }
                dotFlag = TRUE;
            }
        }

        //To escape pseudo-answers
        if (isEnd == TRUE)
        {

            translateNum(&tempNum, digitsBeforePoint);
            tempAns += tempNum;

            *ptrToData = tempAns;
        }

        tempAns = 0;

    _okReturn(LOG_COMMON);
}


int translateNum(double* number, short digitsBeforePoint )
{
    _dumpFunction(LOG_COMMON, translateNum);

        if (*number < 1)
            digitsBeforePoint--;  //skips 0;

        while (digitsBeforePoint-- > 1)
        {
            *number *= 10;
        }

    _okReturn(LOG_COMMON);
}

