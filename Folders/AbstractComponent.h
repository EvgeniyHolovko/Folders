#pragma once
#include <string>
#include <fstream>
#include <windows.h>
class AbstractComponent
{
	std::wstring fullPath;
	std::wstring name;
protected:
	static std::wofstream xmlFileStream;
public:
	AbstractComponent(const wchar_t* path);
	virtual ~AbstractComponent();
	virtual void printXml(void) const = 0;
	virtual void printIfMatch(const wchar_t* findStr) const;
	const wchar_t* getFullPath() const;
	const wchar_t* getName() const;
	static void xmlFileOpen(const wchar_t* fileName);
};

