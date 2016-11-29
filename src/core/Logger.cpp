#include "core/Logger.h"
#include <string>
#include <fstream>
#include <mutex>
#include <iostream>
#include <memory>
#include <ctime>
#include <iomanip>
#include <vector>

namespace Logger
{
	namespace
	{
		std::vector<std::shared_ptr<LoggingPolicy>> policies;
	}

	void ConsolePolicy::write(std::string& line)
	{
		static std::mutex mutex;
		std::lock_guard<std::mutex> lock(mutex);
		std::cout << line << std::endl;
	}

	FilePolicy::FilePolicy(std::string file):
		out(file, std::ios_base::app)
	{}

	void FilePolicy::write(std::string& line)
	{
		if (out)
		{
			std::lock_guard<std::mutex> lock(mutex);
			out << line << std::endl;
		}
	}

	FilePolicy::~FilePolicy()
	{
		if (out)
			out.close();
	}

	LogStream::LogStreamBuf::LogStreamBuf()
	{}

	LogStream::LogStreamBuf::LogStreamBuf(const LogStreamBuf& copy):
		std::stringbuf(copy.str())
	{}

	int LogStream::LogStreamBuf::sync()
	{
		std::string msg = str();

		for (auto i = policies.begin(); i != policies.end(); i++)
			i->get()->write(msg);

		str("");
		return 0;
	}

	LogStream::LogStream():
		std::ostream(&buf)
	{}

	LogStream::LogStream(const LogStream& copy):
		buf(copy.buf),
		std::basic_ios<char>(&buf),
		std::ostream(&buf)
	{}

	void addPolicy(std::shared_ptr<LoggingPolicy> policy)
	{
		policies.push_back(policy);
	}

	void addPolicy(LoggingPolicy *policy)
	{
		policies.push_back(std::shared_ptr<LoggingPolicy>(policy));
	}

	LogStream log(std::string level, std::string tag)
	{
		LogStream stream;
		time_t t = time(0);
		struct tm *now = localtime(&t);
		stream << '[' << std::setw(2) << std::setfill('0') << now->tm_hour;
		stream << ':' << std::setw(2) << std::setfill('0') << now->tm_min;
		stream << ':' << std::setw(2) << std::setfill('0') << now->tm_sec;
		stream << "][" << level << "] " << tag << ": ";
		return stream;
	}

	LogStream debug(std::string tag)
	{
		LogStream stream = log("debug", tag);
		return stream;
	}

	LogStream info(std::string tag)
	{
		return log("info", tag);
	}

	LogStream warn(std::string tag)
	{
		return log("warn", tag);
	}

	LogStream error(std::string tag)
	{
		return log("error", tag);
	}

	void debug(std::string tag, std::string msg)
	{
		debug(tag) << msg << endl;
	}

	void info(std::string tag, std::string msg)
	{
		info(tag) << msg << endl;
	}

	void warn(std::string tag, std::string msg)
	{
		warn(tag) << msg << endl;
	}

	void error(std::string tag, std::string msg)
	{
		error(tag) << msg << endl;
	}

	std::ostream& endl(std::ostream& log)
	{
		log.flush();
		return log;
	}
}
