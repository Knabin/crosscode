#pragma once
class dialog
{
private:
	// getline �̿�
	vector<wstring> _vText;
	vector<class dialogText*> _vObjects;

	int _textIndex;

public:
	dialog(string fileName);
	~dialog();

	bool next();
	void loadText();

};
