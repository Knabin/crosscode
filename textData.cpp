#include "stdafx.h"
#include "textData.h"

textData::textData()
{
}

textData::~textData()
{
}

HRESULT textData::init()
{
	return S_OK;
}

void textData::release()
{
}

void textData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	DWORD write;

	char str[128];

	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);

	CloseHandle(file);
}

char * textData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str));

	//¿ìÁÖ¼± XÁÂÇ¥ 20
	//¿ìÁÖ¼± YÁÂÇ¥ 40
	//¿ìÁÖ¼± Ã¼·Â 100
	//º¤ÅÍ »çÀÌÁî 3
	//20,40,100
	for (int i = 0; i < vArray.size(); ++i)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat_s(str, ",");
	}


	return str;
}

vector<string> textData::txtLoad(const char * loadFileName)
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile(loadFileName, GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);



	return charArraySeparation(str);
}

vector<string> textData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ",";
	char* token;

	//¿ìÁÖ¼± XÁÂÇ¥ 20
	//¿ìÁÖ¼± YÁÂÇ¥ 40
	//¿ìÁÖ¼± Ã¼·Â 100
	//º¤ÅÍ »çÀÌÁî 3
	//20,40,100

	token = strtok_s(charArray, separator, &temp);

	vArray.push_back(token);

	while (NULL != (token = strtok_s(NULL, separator, &temp)))
	{
		vArray.push_back(token);
	}


	return vArray;
}
