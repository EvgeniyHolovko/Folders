#include "stdafx.h"
#include "FileComponent.h"


FileComponent::FileComponent(const wchar_t* fullFilePath) : AbstractComponent(fullFilePath)
{
}

FileComponent::~FileComponent()
{

}

void FileComponent::printXml(void) const
{
	xmlFileStream << "<file " << "name = \"" << getName() << "\" />" << std::endl;
}
