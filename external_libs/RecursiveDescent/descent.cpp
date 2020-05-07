#ifndef RDM_CPP_INCLUDED
#define RDM_CPP_INCLUDED

    char* formatParsingLine(const char* stringToAnalyze, size_t size)
    {
        _dumpFunction(LOG_RDM, formatParsingLine);
        assertRDM(stringToAnalyze != nullptr);



            _writeComment(LOG_RDM, "Allocating memory for formated string...");
            char* tempString = (char*) calloc(size, sizeof(char));


            _writeComment(LOG_RDM, "Copying string symbols except '\\t', ' ' and '\\n'...");
            size_t i = 0, j = 0;
            while (i != size)
            {
                    if ( (stringToAnalyze[i] == ' ')  ||  (stringToAnalyze[i] == '\t')  ||  (stringToAnalyze[i] == '\n') )
                        i++;

                    else
                        tempString[j++] = stringToAnalyze[i++];
            }


        _endOfFunction(LOG_RDM);
        return tempString;
    }



    rdm_data_t mathParser(const char* line, size_t length)
    {
        _initLog(LOG_RDM, "LOG_RDM");
        _dumpFunction(LOG_RDM, mathParser);

        ptrCheck(line, LOG_RDM);
        numCheck(length, LOG_RDM);


            sprintf(_comment, "Parsing math expression (\"%s\")...", line);
            _writeComment(LOG_RDM, _comment);


            //Formatting line
                char* parsingLine = formatParsingLine(line, length);
                ptrCheck(parsingLine, LOG_RDM);

            //Parsing
                RDMStatus = OK; //initialization
                rdm_data_t ans = getG(parsingLine);


            if (RDMStatus != OK)
                _writeComment(LOG_RDM, "#PARSING FAILED");



        _writeComment(LOG_RDM, "Freeing allocated for line memory...");
        free(parsingLine);



        _endOfFunction(LOG_RDM);
        return ans;
    }


    rdm_data_t getG(const char* stringToAnalyze)
    {
        _dumpFunction(LOG_RDM, getG);
        assertRDM(stringToAnalyze != nullptr);

        sprintf(_comment, "Getting expression {looking at \"%s\"}...", stringToAnalyze);
        _writeComment(LOG_RDM, _comment);

            //initialization
            currentSymbol = stringToAnalyze;

                    rdm_data_t ans = getE();
                    RDMstatusChk();

            assertRDM(*currentSymbol == '\0');


        _endOfFunction(LOG_RDM);
        return ans;
    }




    rdm_data_t getE()
    {
        _dumpFunction(LOG_RDM, getE);
        assertRDM(currentSymbol != nullptr);

        sprintf(_comment, "Trying to calculate a polynomial {looking at \"%s\"}...", currentSymbol);
        _writeComment(LOG_RDM, _comment);



            rdm_data_t val = getT();
            RDMstatusChk();


            while ((*currentSymbol == '+') or (*currentSymbol == '-'))
            {
                    if (*(currentSymbol++) == '+')
                    {
                        val += getT();
                        _writeComment(LOG_RDM, "Adding new term...");
                        RDMstatusChk();
                    }


                    else
                    {
                        val -= getT();
                        _writeComment(LOG_RDM, "Substracting new term...");
                        RDMstatusChk();
                    }
            }


        _endOfFunction(LOG_RDM);
        return val;
    }




    rdm_data_t getT()
    {
        _dumpFunction(LOG_RDM, getT);
        assertRDM(currentSymbol != nullptr);

        sprintf(_comment, "Trying to find a monomial {looking at \"%s\"}...", currentSymbol);
        _writeComment(LOG_RDM, _comment);

            rdm_data_t term = getP();
            RDMstatusChk();

            while ((*currentSymbol == '*') or (*currentSymbol == '/'))
            {
                    if (*(currentSymbol++) == '*')
                    {
                        term *= getP();
                        _writeComment(LOG_RDM, "Multiplying to new term...");
                        RDMstatusChk();
                    }


                    else
                    {
                        term /= getP();
                        _writeComment(LOG_RDM, "Dividing to new term...");
                        RDMstatusChk();
                    }
            }

        _endOfFunction(LOG_RDM);
        return term;
    }


    rdm_data_t getP()
    {
        _dumpFunction(LOG_RDM, getP);
        assertRDM(currentSymbol != nullptr);

        sprintf(_comment, "Trying to find an opening bracket {looking at \"%s\"}...", currentSymbol);
        _writeComment(LOG_RDM, _comment);


            if (*currentSymbol == '(')
            {
                currentSymbol++;
                _writeComment(LOG_RDM, "Opening bracket found, restarting algorithm...");
                rdm_data_t polynom = getE();
                RDMstatusChk();


                _writeComment(LOG_RDM, "Checking if expression in brackets ended...");
                assertRDM(*(currentSymbol++) == ')');

                _endOfFunction(LOG_RDM);
                return polynom;
            }


            rdm_data_t ans = getF();
            RDMstatusChk();

        _endOfFunction(LOG_RDM);
        return ans;
    }


    rdm_data_t getF()
    {
        _dumpFunction(LOG_RDM, getF);
        assertRDM(currentSymbol != nullptr);


        sprintf(_comment, "Trying to find a number with a floating point {looking at \"%s\"}...", currentSymbol);
        _writeComment(LOG_RDM, _comment);


        char intFlag = FALSE, fractFlag = FALSE;
        rdm_data_t intPart = 0;
        rdm_data_t fractPart = 0;


        //integer part:
            if (*currentSymbol != '.')
            {
                _writeComment(LOG_RDM, "Getting integer part...");
                intPart = getN();
                RDMstatusChk();
            }


            else
                intFlag = TRUE;

        //fractional part:
            if (*currentSymbol == '.')
            {
                const char* firstSymbol = currentSymbol;
                _writeComment(LOG_RDM, "Getting fractional part...");
                fractPart = getN();
                RDMstatusChk();

                if (firstSymbol == currentSymbol)
                {
                    currentSymbol++;
                    fractFlag = TRUE;
                }

                assertRDM((fractFlag == FALSE) || (intFlag == FALSE));
            }

            while (fractPart >= 1)
                fractPart /= 10;

            _writeComment(LOG_RDM, "Summarizing an integer and a fractional parts...");

        _endOfFunction(LOG_RDM);
        return intPart + fractPart;
    }




    rdm_data_t getN()
    {
        _dumpFunction(LOG_RDM, getN);
        assertRDM(currentSymbol != nullptr);

        sprintf(_comment, "Trying to find an integer expression {looking at \"%s\"}...", currentSymbol);
        _writeComment(LOG_RDM, _comment);


            rdm_data_t val = 0;
            const char* firstChar = currentSymbol;

            if (*firstChar == '.')  //Must look for a '.' at this scope because of exception of parsing the "" line
                currentSymbol++;    //and specific "double" format (e.g. ".1" or "1."); probably needs to be reworked;

                    while (isdigit(*currentSymbol))
                        val = val * 10 + (*currentSymbol++ - '0');

                    if ((*firstChar != '.') && (*firstChar != '-') && (*firstChar != '+')) //because of (-1, +2.415 and etc)
                    {
                        assertRDM(firstChar != currentSymbol);
                        _writeComment(LOG_RDM, "Integer expression found!");
                    }

        _endOfFunction(LOG_RDM);
        return val;
    }

#endif
