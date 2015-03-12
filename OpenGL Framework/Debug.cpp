#include "Debug.h"
#include <iostream>

void rb::Debug::Log(const string& logText)
{
	std::cout << logText << std::endl;
}

void rb::Debug::Info(const string& infoText)
{
	std::cout << "INFO: ";
	Log(infoText);
}

void rb::Debug::Error(const string& errorText)
{
	std::cout << "ERROR: ";
	Log(errorText);
}

void rb::Debug::Warning(const string& warningText)
{
	std::cout << "WARNING: ";
	Log(warningText);
}
