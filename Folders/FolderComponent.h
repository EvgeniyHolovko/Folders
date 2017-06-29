#pragma once
#include "AbstractComponent.h"
#include <vector>
#include <windows.h>


struct MY_BUFFERS {
	static const int	CHAR_BUFF_SIZE = 1024;
	TCHAR				tCharBuff[CHAR_BUFF_SIZE];
	WIN32_FIND_DATA		findFileData;
};

class FolderComponent : public AbstractComponent
{
	std::vector<AbstractComponent*> components;

public:
	FolderComponent(MY_BUFFERS* buff);
	virtual ~FolderComponent();
	virtual void printXml(void) const override;
	virtual void printIfMatch(const wchar_t* findStr) const override;
};

