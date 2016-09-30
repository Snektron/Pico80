#ifndef INCLUDE_LOG_LOGGER_H_
#define INCLUDE_LOG_LOGGER_H_

#include <ostream>
#include <iostream>
#include <string>

using std::string;
using std::ostream;

namespace Logger
{
	void flush();

	ostream& endl(ostream& os);

	ostream& get_stream();

	ostream& debug(string tag);

	ostream& info(string tag);

	ostream& warn(string tag);

	ostream& error(string tag);

	void debug(string tag, string msg);

	void info(string tag, string msg);

	void warn(string tag, string msg);

	void error(string tag, string msg);
}

#endif /* INCLUDE_LOG_LOGGER_H_ */
