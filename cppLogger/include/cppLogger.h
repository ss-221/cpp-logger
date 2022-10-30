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
		inline static LoggerPriority priority = LoggerPriority::Info;
		inline static std::mutex loggerMutex;
		inline static FILE* filePtr = 0;

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
				fprintf(filePtr, "%s", timeStampBuffer);

				std::ostringstream oss;
				oss << std::this_thread::get_id();
				fprintf(filePtr, "[");
				fprintf(filePtr, oss.str().c_str());
				fprintf(filePtr, "] ");
				
				fprintf(filePtr, priorityVal);
				fprintf(filePtr, msg, args...);
				fprintf(filePtr, "\n");
			}
			
		}

		~Logger()
		{	
			LogClose();
		}

	public:

		template<typename... Args>
		static void LogClose()
		{
			if (filePtr != 0)
			{
				printer(LoggerPriority::Error, "[*] ", "Log Closed.");
				fclose(filePtr);
				filePtr = 0;
			}
		}

		template<typename... Args>
		static void LogOpen(const char* filePath)
		{
			if (filePtr != 0)
			{
				LogClose();
			}

			fopen_s(&filePtr, filePath, "a");
			printer(LoggerPriority::Error, "[*] ", "Log Opened.");
		}

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
}

#endif





