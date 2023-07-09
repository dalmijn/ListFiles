#pragma once

#include <ctime>

class Log
{
public:
	enum Level
	{
		LevelError, LevelWarning, LevelInfo
	};
private:
	Level m_Loglevel = LevelInfo;
public:
	void SetLevel(Level level)
	{
		m_Loglevel = level;
	}

	void Error(std::string message)
	{
		if (m_Loglevel >= LevelError)
			std::cout << "[Error]: " << message << std::endl;
	}

	void Warn(std::string message)
	{
		if (m_Loglevel >= LevelWarning)
			std::cout << "[Warning]: " << message << std::endl;
	}

	void Info(std::string message)
	{
		if (m_Loglevel >= LevelInfo)
			std::cout << "[Info]: " << message << std::endl;
	}
};