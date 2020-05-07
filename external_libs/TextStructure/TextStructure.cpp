//ver 2

//20.01.19
#ifndef TEXT_CPP_INCLUDED
#define TEXT_CPP_INCLUDED



int textCtor(text_t* textStruct, const char* fileName, const char* rules)
{
	//assert(textStruct);
	assert(fileName);
	assert(rules);
	assert(LOG_TEXT);
	_initLog(LOG_TEXT, "LOG_TEXT");
	_dumpFunction(LOG_TEXT, textCtor);


	ptrCheck(textStruct, LOG_TEXT);


	if (openFile(textStruct, fileName, rules) != OK)
		_failReturn(LOG_TEXT);


	_okReturn(LOG_TEXT);
}


int formatSpaces(text_t* text)
{

	_dumpFunction(LOG_TEXT, formatSpaces);
	ptrCheck(text, LOG_TEXT);

	_writeComment(LOG_TEXT, "Allocating memory for the formatted string...");
	char* newBuf = (char*) calloc((*text).bufSize, sizeof(char));

//printf("MAX PTR IS %p\n", newBuf + (*text).bufSize);
	ptrCheck(newBuf, LOG_TEXT);
	ptrCheck((*text).buf, LOG_TEXT);
	size_t oldIDX = 0, newIDX = 0, linesIDX = 0;


	size_t linesCount = countChar((*text).buf, '\n');




	#define charFormat ((*text).buf + oldIDX)
	#define skipSpaces while ((*charFormat == ' ') || (*charFormat == '\t')) oldIDX++;


	//printf("", (*text).buf);
	for (linesIDX = 0; linesIDX < linesCount - 1; linesIDX++)
	{

		//printf(" \n__________________________________________________________________________\nlooking at %s\n-----------------------------------------------------------------\n", (*text).buf + oldIDX);

		skipSpaces;

		while (*charFormat != '\n')
		{


			while ((*charFormat != ' ') && (*charFormat != '\t') && (*charFormat != '\n') )
			{
				//printf("oldIDX %d\n", oldIDX);
				//printf("newptr is %p\n", newBuf + newIDX);

				newBuf[newIDX++] = *charFormat;
				oldIDX++;
			}

			if ((*charFormat == ' ') || (*charFormat == '\t'))
			{

				newBuf[newIDX++] = *charFormat;
				oldIDX++;
				skipSpaces;

			}


		}
		newBuf[newIDX++] = '\n';
		oldIDX++;
	}



	//Last line
		{
			skipSpaces;

			while (*charFormat != '\0')
			{

				while ((*charFormat != ' ') && (*charFormat != '\t') && (*charFormat != '\0'))
				{
					newBuf[newIDX++] = *charFormat;
					oldIDX++;
				}

				if ((*charFormat == ' ') || (*charFormat == '\t'))
				{
					newBuf[newIDX++] = *charFormat;
					oldIDX++;
					skipSpaces;
				}

			}

			newBuf[newIDX++] = '\0';

		}




	#undef charFormat

	sprintf(_comment, "Formatted line is:\n%s\n\n", newBuf);


	_writeComment(LOG_TEXT, _comment);

	newBuf = (char*) realloc(newBuf, newIDX);
	free((*text).buf);
	(*text).buf		= newBuf;
	(*text).bufSize = newIDX;
	(*text).bufCap 	= newIDX;


	_okReturn(LOG_TEXT);
}


size_t countChar(char* buf, char ch)
{
	_dumpFunction(LOG_TEXT, countChar);
		ptrCheck(buf, LOG_TEXT);


		size_t ans = 0, IDX = 0;

		while(buf[IDX] != '\0')
			if (buf[IDX++] == ch)
				ans++;



	_endOfFunction(LOG_TEXT);
	return ans;
}

int openFile(text_t* text, const char* path, const char* rules)
{
	assert(text);
	assert(path);
	assert(rules);
	assert(LOG_TEXT);
	_dumpFunction(LOG_TEXT, openFile);

	ptrCheck(text, LOG_TEXT);
	ptrCheck(path, LOG_TEXT);
	ptrCheck(rules, LOG_TEXT);

	if (fileIsClosed(text) == TRUE)
	{
		(*text).file = fopen(path, rules);
		if (!(*text).file)
			_bindErr(CANT_OPEN_FILE);

		_writeComment(LOG_TEXT, "Opening file...");

		if (_status == OK)
		{
			(*text).isFileClosed = FALSE;
		}

		readFile(text);

	}


	_statusReturn(LOG_TEXT);
}



int readFile(text_t* textStruct)
{
	assert(LOG_TEXT);
	assert(textStruct);
   _dumpFunction(LOG_TEXT, readFile);
   _writeComment(LOG_TEXT, "Reading file...");

    ptrCheck(textStruct, LOG_TEXT);

	if (fileIsClosed(textStruct) == FALSE)
	{
		//Allocating memory:
	    //----------------------------
			size_t fileSize = 0;
	    	getSizeOfFile(textStruct, &fileSize);

	    	(*textStruct).buf = (char*) calloc(fileSize, sizeof(char));
			assert((*textStruct).buf);
	    	if ((*textStruct).buf == nullptr)
	    	{
	        	(*textStruct).bufCap = 0;
				(*textStruct).bufSize = 0;
	        	_bindErr(NOT_ENOUGH_SPACE);
	    	}

	    	_writeComment(LOG_TEXT, "Allocating memory...");

			if (_status == FAIL)
	        	_failReturn(LOG_TEXT);
	    //--------------------------------------------------------------------

	    (*textStruct).bufCap = fileSize;

	    //Reading file:
	    //---------
		ptrCheck((*textStruct).file, LOG_TEXT);
	    (*textStruct).bufSize = fread((*textStruct).buf, sizeof(char), fileSize, (*textStruct).file);
	    //----------
		_okReturn(LOG_TEXT);
	}

	_bindErr(FILE_IS_CLOSED);
	_writeComment(LOG_TEXT, "File is closed, exiting...");
	_failReturn(LOG_TEXT);
}




int textDtor(text_t* textStruct)
{
	assert(textStruct);
	assert(LOG_TEXT);
	_dumpFunction(LOG_TEXT, textDtor);
	sprintf(_comment, "Destructing text (%p)...", textStruct);
	_writeComment(LOG_TEXT, _comment);


		ptrCheck(textStruct, LOG_TEXT);

		closeText(textStruct);
		free((*textStruct).buf);

		*textStruct = {0, 0, 0, 0};

	_okReturn(LOG_TEXT);
}



int closeText(text_t* text)
{
	assert(LOG_TEXT);
	assert(text);
	_dumpFunction(LOG_TEXT, closeText);
	_writeComment(LOG_TEXT, "Closing text...");

		ptrCheck(text, LOG_TEXT);

		if (fileIsClosed(text) == TRUE)
		{
			_writeComment(LOG_TEXT, "#File is already closed!");
			_failReturn(LOG_TEXT);
		}

		ptrCheck((*text).file, LOG_TEXT);
		fclose((*text).file);
		(*text).file = nullptr;
		(*text).isFileClosed = TRUE;

	_statusReturn(LOG_TEXT);
}




int fileIsClosed(text_t* text)
{
		assert(text);
		assert(LOG_TEXT);
		_dumpFunction(LOG_TEXT, fileIsClosed);
		_writeComment(LOG_TEXT, "Checking if file is closed...");

				ptrCheck(text, LOG_TEXT);

				switch ((*text).isFileClosed)
				{
					case TRUE:	if ((*text).file != nullptr)
								{
									_bindErr(TEXT_CLOSED_INCORRECTLY);
									_writeComment(LOG_TEXT, "Checking file pointer...");
									_failReturn(LOG_TEXT);
								}

								_endOfFunction(LOG_TEXT);
								return TRUE;

					case FALSE:	if ((*text).file == nullptr)
								{
									_bindErr(DEAD_POINTER);
									_writeComment(LOG_TEXT, "Checking pointer to file...");
									_failReturn(LOG_TEXT);
								}
								_endOfFunction(LOG_TEXT);
								return FALSE;

					default:
								_bindErr(UNKNOWN_ERROR);
								_writeComment(LOG_TEXT, "Checking TextStructure's Flag...");
								_failReturn(LOG_TEXT);
				}


		_endOfFunction(LOG_TEXT);
		return FALSE;
}



int getSizeOfFile(text_t* textStruct, size_t* sizeOfFile)
{
	assert(textStruct);
	assert(sizeOfFile);
	assert(LOG_TEXT);
	_dumpFunction(LOG_TEXT, getSizeOfFile);
	_writeComment(LOG_TEXT, "Counting file size...");

			ptrCheck(textStruct, LOG_TEXT);
			ptrCheck(sizeOfFile, LOG_TEXT);

			if (fileIsClosed(textStruct) == TRUE)
			{
					_bindErr(FILE_IS_CLOSED);
					_writeComment(LOG_TEXT, "File is closed, exiting...");
					_failReturn(LOG_TEXT);
			}

			ptrCheck((*textStruct).file, LOG_TEXT);
			size_t i = ftell((*textStruct).file);
			fseek((*textStruct).file, 0, SEEK_END);
			*sizeOfFile = ftell((*textStruct).file);
			fseek((*textStruct).file, 0, i);

	_okReturn(LOG_TEXT);
}


int textBufAppend(text_t* textStructure, const char* textToAdd) //strcat
{
	assert(LOG_TEXT);
	assert(textStructure);
	assert(textToAdd);
    _dumpFunction(LOG_TEXT, textBufAppend);
	sprintf(_comment, "Appending text to text structure (%p)...", textStructure);
	_writeComment(LOG_TEXT, _comment);

    //Checking PTRs:
        ptrCheck(textStructure, LOG_TEXT);
		ptrCheck(textToAdd, LOG_TEXT);

    //Count new text length:
    //-----
        size_t newTextLength = -1;
        while (textToAdd[++newTextLength] != '\0');
    //-----

    //Adding memory:
    //--------
		void* tempPtr = nullptr;

		if (!(*textStructure).buf)
			tempPtr = calloc(newTextLength, sizeof(char));

		else
			tempPtr = realloc((*textStructure).buf, (newTextLength + (*textStructure).bufSize));


        if (tempPtr == nullptr)
		{
			_bindErr(NOT_ENOUGH_SPACE);
			_writeComment(LOG_TEXT, "Allocating memory...");
        	_failReturn(LOG_TEXT);
        }

		_writeComment(LOG_TEXT, "Allocating memory...");

        (*textStructure).buf = (char*) tempPtr;
        (*textStructure).bufCap = (newTextLength + (*textStructure).bufSize);
    //----


    //Adding a new string:
    //-----
        size_t  j = 0;
        while ((*textStructure).buf[(*textStructure).bufSize++] = textToAdd[j++] != '\0');

    _okReturn(LOG_TEXT);
}





int divTextCtor(char* textBuf, size_t bufLength, char div, div_text_t* result)
{
	_dumpFunction(LOG_TEXT, divTextCtor);
	sprintf(_comment, "Dividing text by character (int %d)...", div);
	_writeComment(LOG_TEXT, _comment);
	assert(textBuf);
	assert(result);


	ptrCheck(textBuf, LOG_TEXT);
	ptrCheck(result, LOG_TEXT);



		(*result).divided = (elem_text_t*) calloc(bufLength, sizeof(elem_text_t));

		int symbIDX = -1, elemIDX = 0, elemLength = 0, maxLength = 0;

		//(*result).divided[countLines].pointer = buffer;

		if ((*result).divided == nullptr)
		{
			_bindErr(NOT_ENOUGH_SPACE);
			_writeComment(LOG_TEXT, "Allocating memory...");
		       	_failReturn(LOG_TEXT);
		}


		ptrCheck(textBuf, LOG_TEXT);

		while (textBuf[++symbIDX] == div);


		(*result).divided[0].first = textBuf + symbIDX;

		while ((textBuf[++symbIDX] != '\0') && (symbIDX < bufLength))
			if (textBuf[symbIDX] == div)
			{
				_writeComment(LOG_TEXT, "Found new element!");
				(*result).divided[elemIDX].length = textBuf + symbIDX - 1 - (*result).divided[elemIDX].first;

				while (textBuf[++symbIDX] == div)
					_writeComment(LOG_TEXT, "Skipping repeating dividing character...");

				elemIDX++;

				if (textBuf[symbIDX] != '\0')
					(*result).divided[elemIDX].first = textBuf + symbIDX;

				else
				{
					elemIDX--;
					symbIDX--;
				}
			}


		(*result).divided[elemIDX].length = textBuf + symbIDX + 1 - (*result).divided[elemIDX].first;

		(*result).count = elemIDX + 1;

	_okReturn(LOG_TEXT);
}




int divTextDtor(div_text_t* text)
{
	_dumpFunction(LOG_TEXT, divTextDtor);
	ptrCheck(text, LOG_TEXT);

		free((*text).divided);
		(*text).count = 0;

	_okReturn(LOG_TEXT);
}




int printDivText(div_text_t* text)
{
	_dumpFunction(LOG_TEXT, printDivText);

		ptrCheck(text, LOG_TEXT);
		ptrCheck((*text).divided, LOG_TEXT);

		for (size_t i = 0; i < (*text).count; i++)
		{
			printf("elem %d, length is %d:\n", i, (*text).divided[i].length);
			char* first = (*text).divided[i].first;
			char* last = (*text).divided[i].first + (*text).divided[i].length;

			for (char* j = first; j <= last; j++)
			{
				ptrCheck(j, LOG_TEXT);
				putchar(*j);
			}

			putchar('\n');
			putchar('\n');
		}

	_okReturn(LOG_TEXT);
}


char* stringCopy(char* stringPtr, size_t nmemb)
{
	_dumpFunction(LOG_TEXT, stringCopy);

	if (stringPtr == nullptr)
	{
		_bindErr(DEAD_POINTER);
		_writeComment(LOG_TEXT, "Checking pointer...");
		return nullptr;
	}

		char* copied = (char*) calloc(nmemb, sizeof(char));
		for (size_t i = 0; i < nmemb; i++)
			copied[i] = stringPtr[i];

	_endOfFunction(LOG_TEXT);
	return copied;
}




#endif
