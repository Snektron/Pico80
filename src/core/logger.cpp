#include <core/Logger.h>
#include <ostream>
#include <ctime>
#include <iomanip>

using std::string;
using std::ostream;

ostream& logout = std::cout;

void logtime(ostream& out)
{
	time_t t = time(0);
	struct tm *now = localtime(&t);
	out << '[' << std::setw(2) << std::setfill('0') << now->tm_hour;
	out << ':' << std::setw(2) << std::setfill('0') << now->tm_min;
	out << ':' << std::setw(2) << std::setfill('0') << now->tm_sec << ']';
}

void loglevel(ostream& out, string level)
{
	out << "[" << level << "] ";
}

void logtag(ostream& out, string tag)
{
	out << tag << ": ";
}

ostream& loghdr(ostream& out, string level, string tag)
{
	logtime(out);
	loglevel(out, level);
	logtag(out, tag);
	return out;
}

void Logger::flush()
{
	get_stream().flush();
}

ostream& Logger::endl(ostream& os)
{
	return os << std::endl;
}

ostream& Logger::get_stream()
{
	return logout;
}

ostream& Logger::debug(string tag)
{
	return loghdr(get_stream(), "debug", tag);
}

ostream& Logger::info(string tag)
{
	return loghdr(get_stream(), "info", tag);
}

ostream& Logger::warn(string tag)
{
	return loghdr(get_stream(), "warn", tag);
}

ostream& Logger::error(string tag)
{
	return loghdr(get_stream(), "error", tag);
}

void Logger::debug(string tag, string msg)
{
	debug(tag) << msg << Logger::endl;
}

void Logger::info(string tag, string msg)
{
	info(tag) << msg << Logger::endl;
}

void Logger::warn(string tag, string msg)
{
	warn(tag) << msg << Logger::endl;
}

void Logger::error(string tag, string msg)
{
	error(tag) << msg << Logger::endl;
}
