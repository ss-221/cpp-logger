#ifndef CPPLOGGER_H
#define CPPLOGER_H

#include <iostream>
#include <ctime>
#include <mutex>
#include <thread>
#include <sstream>

namespace cppLogger {

	enum class LoggerPriority
	{
		Error,
		Info,
		Debug		
	};

	class Logger
	{
	private:

		Logger();
		static LoggerPriority priority;
		static std::mutex loggerMutex;

		template<typename... Args>
		static void printer(LoggerPriority msgPriority, const char* priorityVal, const char* msg, Args... args)
		{
			if (priority >= msgPriority)
			{
				std::scoped_lock lock(loggerMutex);

				std::time_t currTime = std::time(0);
				std::tm timeStamp;
				localtime_s(&timeStamp, &currTime);
				char timeStampBuffer[100];
				strftime(timeStampBuffer, 100, "%F %T ", &timeStamp);
				printf("%s", timeStampBuffer);

				std::ostringstream oss;
				oss << std::this_thread::get_id();
				printf("[%s] ", oss.str().c_str());
				
				printf(priorityVal);
				printf(msg, args...);
				printf("\n");
			}
			
		}

	public:

		static void setPriority(LoggerPriority priorityToSet)
		{
			priority = priorityToSet;
		}

		static Logger& getLoggerInstance()
		{
			static Logger instance;
			return instance;
		}

		template<typename... Args>
		static void ERRORMSG(const char* msg, Args... args)
		{
			printer(LoggerPriority::Error, "[ERROR] ", msg, args...);
		}

		template<typename... Args>
		static void INFOMSG(const char* msg, Args... args)
		{
			printer(LoggerPriority::Info, "[INFO] ", msg, args...);
		}		

		template<typename... Args>
		static void DEBUGMSG(const char* msg, Args... args)
		{
			printer(LoggerPriority::Debug, "[DEBUG] ", msg, args...);
		}

	};

	LoggerPriority Logger::priority = LoggerPriority::Info;
	std::mutex Logger::loggerMutex;
}

#endif





