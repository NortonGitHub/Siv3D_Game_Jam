#pragma once
#include <string>
#include "FileReadBase.h"
class FileReadFactory
{
public:
	FileReadFactory();
	~FileReadFactory();

	FileReadBase* createInstance(std::string fileName);
	
protected:
	virtual FileReadBase* createFileRead(std::string fileName) = 0;
	virtual FileReadBase* registerFileRead(FileReadBase* fileReader) = 0;
};

