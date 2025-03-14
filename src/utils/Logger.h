#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include "ConsoleColor.h"

class Logger
{
protected:
	std::string getTimestampShort();
	std::string getTimestamp();
	const char* _name;

public:
	Logger() : _name(nullptr) {}
	Logger(const char* name) : _name(name) {}

	void logInfo(const std::string& message);
	void logWarning(const std::string& message);
	void logError(const std::string& message);
	void log(const std::string& message, const char* logTitle, ConsoleColor color);
};

#endif