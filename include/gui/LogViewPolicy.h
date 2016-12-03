#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QObject>
#include <iostream>
#include <mutex>
#include "core/Logger.h"
#include "gui/LogModel.h"

class LogViewPolicy : public Logger::LoggingPolicy
{
private:
	LogModel *model;
	std::mutex mutex;

public:
	LogViewPolicy(LogModel *model):
		model(model)
	{}

	void write(std::string& line)
	{
		std::lock_guard<std::mutex> lock(mutex);
		model->write(QString(line.c_str()));
	}
};

#endif // LOGVIEW_H
