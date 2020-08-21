#pragma once
class dialog
{
private:
	// getline ÀÌ¿כ
	vector<wstring> _vText;
	vector<class dialogText*> _vObjects;

	class portrait* lea;
	class portrait* pro;

	int _textIndex;
	string _fileName;

public:
	dialog(string fileName);
	~dialog();

	bool next();
	void loadText();

};
