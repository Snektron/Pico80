#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QObject>
#include <iostream>
#include "core/Logger.h"

#define MAX_LOG_BUF 8000

class LogViewPolicy : public Logger::LoggingPolicy
{
private:
	QObject *logview;
	QString log;
public:
	LogViewPolicy(QObject *logview):
		logview(logview),
		log("")
	{
		logview->setProperty("text", QVariant(""));
	}

	void write(std::string& line)
	{
		log.append(line.c_str());
		log.append('\n');
		if (log.size() > MAX_LOG_BUF)
		{
			log = log.right(MAX_LOG_BUF);
			log = log.right(log.size() - log.indexOf("\n") - 1);
		}
		logview->setProperty("text", QVariant(log));
	}
};

#endif // LOGVIEW_H
