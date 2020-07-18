#pragma once
class textData
{
public:
	static textData* getInstance()
	{
		static textData instance;
		return &instance;
	}
private:
	textData();
	~textData();

public:
	HRESULT init();
	void release();

	void txtSave(const char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	vector<string> txtLoad(const char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);
};