//28.10.18

//Editing Log's structure functions:
#include <assert.h>

//int _statusCheck()

int _initLog(logf_t* log, const char* path)
{
	assert(log);
	assert(path);


	if (log == nullptr)
		return 1;



	if (path == nullptr)
		return 1;

	static char initCounts = 0;

	//Saving filename
	int len = 0;
	while (path[++len] != '\0');



	(*log).path = (char*) calloc(len, sizeof(char));

	for (int i = 0; i <= len; i++)
		(*log).path[i] = path[i];


	//Opening file:
	if ((*log).isFileClosed == TRUE)
	{



		_openLog(log);




		fprintf((*log).file, "\nLOG_INITIALIZATION #%d\n\n=================================================\n", ++initCounts);
		return 0;
	}

	return 1;
}


int _openLog(logf_t* log)
{


	assert(log);


	if (log == nullptr)
		return 1;

	const char* path = (*log).path;

	assert(path);
	if (path == nullptr)
		return 1;



	if ((*log).isFileClosed == TRUE)
	{




		(*log).file = fopen(path, "a");	//a is for append


		(*log).isFileClosed = FALSE;
		return 0;
	}



	return 1;
}


int _closeLog(logf_t* log)
{
	assert(log);
	if (log == nullptr)
			return 1;

	if ((*log).isFileClosed == FALSE)
	{
			fclose((*log).file);
			(*log).isFileClosed = TRUE;
			return 0;
	}

	return 1;
}



int _logBufAppend(logf_t* log, const char* textToAdd)
{
	assert(log);
	assert(textToAdd);

	if (log == nullptr)
		return 1;

	if (textToAdd == nullptr)
		return 1;

	//Count new text length:
	//-----
		size_t newTextLength = -1;
		while (textToAdd[++newTextLength] != '\0');
	//-----

	//printf("textLength %lu\n", newTextLength);
	_openLog(log);
	fwrite(textToAdd,  sizeof(char), newTextLength, (*log).file);
	_closeLog(log);

	return 0;
}





int _writeToDump(char* dumpElem, const char* text)
{
	assert(dumpElem);
	assert(text);

	if (dumpElem == nullptr)
			return 1;
	if (text == nullptr)
			return 1;

	int i = -1;
	while ((dumpElem[i] = text[++i]) != '\0');

	return 0;
}


int _writeComment(logf_t* logPtr, const char* comment)
{
	assert(logPtr);
	assert(comment);

	if (logPtr == nullptr)
		return 1;

	if (comment == nullptr)
		return 1;


		char *tabs = 0, *funcTabs = 0, tempString[commentLength] = {}, tab = '\t';
		static int numeration = 0, countActTabs = 1;
		tabs = _tabsGen(countActTabs, tab, TRUE);
		int i = 0;


		if (comment[0] == '$')
		{
			if (countActTabs > 1)
				sprintf(tempString, "%s\n%s_%s\n%s|\n", tabs, tabs, comment + 1, tabs);

			else
				sprintf(tempString, "%s\n%s_%s\n%s\n", tabs, tabs, comment + 1, tabs);

			_logBufAppend(logPtr, tempString);
			countActTabs++;
		}

		else if (comment[0] == '#')
		{
			sprintf(tempString, "CONSIDER!\n%s\n", comment + 1);
			_logBufAppend(logPtr, tempString);
		}

		else if (comment[0] == '@')
		{
			sprintf(tempString, "%s\n", tabs);

			tabs[(countActTabs--) * 2 - 2] = '\0';


			sprintf(tempString, "%s%s_%s\n", tempString, tabs, comment + 1);
			tabs[(countActTabs) * 2 - 2] = '\0';
			sprintf(tempString, "%s%s\n", tempString, tabs);


			_logBufAppend(logPtr, tempString);
		}

		else
		{
			sprintf(tempString, "%sact %d: %s\n", tabs, numeration++, comment);
			_logBufAppend(logPtr, tempString);

			if (dump.errNo != 0)
			{
				sprintf(tempString, "%s\n", failMessage);
				_logBufAppend(logPtr, tempString);
				unsigned i = 0;
				for (i = 0; i < dump.curFuncNo; i++)
				{
					funcTabs = _tabsGen(i + 1, '-', FALSE);
					sprintf(tempString, "%s%s\n", funcTabs, dump.funcsTree[i]);
					_logBufAppend(logPtr, tempString);
					free(funcTabs);
				}

				sprintf(tempString, "|Error #%d (%s)\n+---------\n", dump.errNo, dump.errName);
				_logBufAppend(logPtr, tempString);
				dump.errNo = 0;
			}
		}

	free(tabs);
	return 0;
}




char* _tabsGen(int count, char tab, int sepCheck)
{
    char* tabs = (char*) calloc(2 * count + 2, sizeof(char)); //tabs[count] : '\0'

    int i = 0;

    if (sepCheck == TRUE)
	{
			/*
				tabs[i++] = '\t';
				tabs[i++] = '|';
			*/
		for (i = 0; i < 2 * count; i += 2)
		{
			tabs[i] = tab;
			tabs[i + 1] = '|';
		}

		if ( (count > 1))
				tabs[i - 1] = '\0';

		return tabs;
	}


		for (i = 0; i <= count; i++)
				tabs[i] = tab;

    tabs[count - 1] = '|';

    return tabs;
}
