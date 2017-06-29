// Folders.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <io.h>
#include "FolderComponent.h"

int _tmain(int argc, wchar_t* argv[])
{
	if (argc != 2) return -1;

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	std::wstring param(argv[1]);
	if (param.at(param.length() - 1) == L'\\' || param.at(param.length() - 1) == L'\"') {
		param.pop_back();
	}
	MY_BUFFERS buff;
	wcscpy_s(buff.tCharBuff, param.c_str());
	FolderComponent* pRootFolderComponent = nullptr;
	HANDLE hFind = FindFirstFile(buff.tCharBuff, &buff.findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		if (buff.findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			pRootFolderComponent = new FolderComponent(&buff);
		}
	}
	if (pRootFolderComponent != nullptr) {
		wchar_t keyWord[80];
		std::wcout << L"Enter your keyword: ";
		std::wcin.getline(keyWord, 80) ;
		pRootFolderComponent->printIfMatch(keyWord);
		std::wcout << L"Press enter to exit...";
		std::wcin.getline(keyWord, 80);
		AbstractComponent::xmlFileOpen(L"Folders.xml");
		pRootFolderComponent->printXml();
		delete pRootFolderComponent;
		return 0;
	}
	return -1;
}
