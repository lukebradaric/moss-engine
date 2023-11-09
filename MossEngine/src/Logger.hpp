#pragma once

#include "windows.h"
#include <string>
#include <iostream>
#include <iomanip>

#include "Color.hpp"

class Logger
{
public:
	static void LogInfo(const char* message)
	{
		Log(message, Color::Blue, "Info");
	}

	static void LogWarning(const char* message)
	{
		Log(message, Color::Yellow, "Warning");
	}

	static void LogError(const char* message)
	{
		Log(message, Color::Red, "Error");
	}

	static void Log(const char* message = "", Color color = Color::White, const char* title = "Log")
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);

		std::time_t time = std::time(0);
		struct std::tm now;
		localtime_s(&now, &time);

		std::cout << '[' << std::put_time(&now, "%H:%M:%S") << "] ";
		std::cout << '[' << title << "] ";
		std::cout << message << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)Color::White);
	}
};