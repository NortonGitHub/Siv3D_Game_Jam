#include "FileReadFactory.h"



FileReadFactory::FileReadFactory()
{
}


FileReadFactory::~FileReadFactory()
{
}

FileReadBase* FileReadFactory::createInstance(std::string fileName)
{
	FileReadBase* fileReader = createFileRead(fileName);
	registerFileRead(fileReader);
	return fileReader;
}
