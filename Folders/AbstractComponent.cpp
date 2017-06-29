#include "stdafx.h"
#include "AbstractComponent.h"
#include <iostream>
#include <fcntl.h>
#include <locale>
#include <codecvt>

std::wofstream AbstractComponent::xmlFileStream;

AbstractComponent::AbstractComponent(const wchar_t * path) : fullPath(path),
			name(fullPath.rfind(L'\\') != std::string::npos ? fullPath.substr(fullPath.rfind(L'\\')+1) : fullPath)
{
}

AbstractComponent::~AbstractComponent()
{
}

void AbstractComponent::printIfMatch(const wchar_t * findStr) const
{
	if (name.find(findStr) != std::string::npos) {
		std::wcout << fullPath << std::endl;
	}
}

const wchar_t * AbstractComponent::getFullPath()  const
{
	return fullPath.c_str();
}

const wchar_t * AbstractComponent::getName()  const
{
	 return name.c_str();
}

void AbstractComponent::xmlFileOpen(const wchar_t* fileName)
{
	xmlFileStream.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::generate_header>));
	xmlFileStream.open(fileName, std::ofstream::out | std::ofstream::trunc);
	xmlFileStream << L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
}
