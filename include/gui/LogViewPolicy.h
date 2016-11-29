#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QObject>
#include "core/Logger.h"

class LogViewPolicy : public Logger::LoggingPolicy
{
private:
	QObject *logview;
public:
	LogViewPolicy(QObject *logview):
		logview(logview)
	{}

	void write(std::string& line)
	{
		QString text = logview->property("text").toString();
		text.append(line.c_str());
		text.append('\n');
		logview->setProperty("text", QVariant(text));
	}
};

#endif // LOGVIEW_H
