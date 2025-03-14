#include "Logger.h"
#include "windows.h"
#include <iomanip>
#include <sstream>
#include <iostream>

void Logger::logInfo(const std::string& message)
{
	log(message, "Info", ConsoleColor::Blue);
}

void Logger::logWarning(const std::string& message)
{
	log(message, "Warning", ConsoleColor::Yellow);
}

void Logger::logError(const std::string& message)
{
	log(message, "Error", ConsoleColor::Red);
}

void Logger::log(const std::string& message, const char* logTitle = "Info", ConsoleColor color = ConsoleColor::White)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);

	std::cout << '[' << getTimestampShort() << "] ";
	std::cout << '[' << logTitle << "] ";
	if (_name != nullptr) std::cout << '[' << _name << "] ";
	std::cout << message << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)ConsoleColor::White);
}

std::string Logger::getTimestampShort()
{
	std::time_t time = std::time(0);
	struct std::tm now;
	localtime_s(&now, &time);

	std::ostringstream stringStream;
	stringStream << std::put_time(&now, "%H:%M:%S");
	return stringStream.str();
}

std::string Logger::getTimestamp()
{
	std::time_t time = std::time(nullptr);
	std::tm now = *std::localtime(&time);

	std::ostringstream stringStream;
	stringStream << std::put_time(&now, "%d-%m-%Y: %H:%M:%S");
	return stringStream.str();
}
