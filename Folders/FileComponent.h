#pragma once
#include "AbstractComponent.h"
class FileComponent : public AbstractComponent
{
public:
	FileComponent(const wchar_t* fullFilePath);
	virtual ~FileComponent();
	virtual void printXml(void) const override;
};

