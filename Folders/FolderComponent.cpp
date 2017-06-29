#include "stdafx.h"
#include "FolderComponent.h"
#include "FileComponent.h"
#include <iostream>
#include <codecvt>

FolderComponent::FolderComponent(MY_BUFFERS* buff) : AbstractComponent(buff->tCharBuff)
{
	HANDLE hFind;
	wcscat_s(buff->tCharBuff, L"\\*");
	hFind = FindFirstFile(buff->tCharBuff, &buff->findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(buff->findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && (!wcscmp(buff->findFileData.cFileName, L".") |
								!wcscmp(buff->findFileData.cFileName, L"..")))) {
				wcscpy_s(buff->tCharBuff, getFullPath());
				wcscat_s(buff->tCharBuff, L"\\");
				wcscat_s(buff->tCharBuff, buff->findFileData.cFileName);
				AbstractComponent* pComponent;
				if (buff->findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					pComponent = new FolderComponent(buff);
				}
				else {
					pComponent = new FileComponent(buff->tCharBuff);
				}
				components.push_back(pComponent);
			}
		} while (FindNextFile(hFind, &buff->findFileData));
		FindClose(hFind);
	}
}

FolderComponent::~FolderComponent()
{
	for (AbstractComponent* pComponent : components) {
		delete(pComponent);
	}
}

void FolderComponent::printXml(void) const
{
	xmlFileStream << "<folder name = \"" << getName() << "\">" << std::endl;
	for (AbstractComponent* pComponent : components) {
		pComponent->printXml();
	}
	xmlFileStream << "</folder>" << std::endl;
}

void FolderComponent::printIfMatch(const wchar_t * findStr) const
{
	AbstractComponent::printIfMatch(findStr);
	for (AbstractComponent* pComponent : components) {
		pComponent->printIfMatch(findStr);
	}
}
