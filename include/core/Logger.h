#ifndef SRC_LOGGER_H_
#define SRC_LOGGER_H_

#include <string>
#include <fstream>
#include <mutex>
#include <sstream>
#include <memory>

namespace Logger
{
	class LoggingPolicy
	{
	public:
		virtual void write(std::string& line) = 0;
		virtual ~LoggingPolicy() = default;
	};

	class ConsolePolicy: public LoggingPolicy
	{
	public:
		void write(std::string& line);
	};

	class FilePolicy: public LoggingPolicy
	{
	private:
		std::ofstream out;
		std::mutex mutex;

	public:
		FilePolicy(std::string file);
		void write(std::string& line);
		~FilePolicy();
	};

	class LogStream: public std::ostream
	{
	private:
		class LogStreamBuf: public std::stringbuf
		{
		public:
			LogStreamBuf();
			LogStreamBuf(const LogStreamBuf& copy);
			int sync();
		};

		LogStreamBuf buf;

	public:
		LogStream();
		LogStream(const LogStream& copy);
	};

	void addPolicy(std::shared_ptr<LoggingPolicy> policy);
	void addPolicy(LoggingPolicy *policy);

	LogStream log(std::string level, std::string tag);

	LogStream debug(std::string tag);
	LogStream info(std::string tag);
	LogStream warn(std::string tag);
	LogStream error(std::string tag);

	void debug(std::string tag, std::string msg);
	void info(std::string tag, std::string msg);
	void warn(std::string tag, std::string msg);
	void error(std::string tag, std::string msg);

	std::ostream& endl(std::ostream& log);
}

#endif /* SRC_LOGGER_H_ */
