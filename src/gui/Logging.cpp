#include "gui/Logging.h"
#include <iostream>

QString fromType(QtMsgType type)
{
	switch (type)
	{
	case QtDebugMsg:
		return "Debug";
	case QtWarningMsg:
		return "Warning";
	case QtCriticalMsg:
		return "Critical";
	case QtFatalMsg:
		return "Fatal";
	case QtInfoMsg:
		return "Info";
	}

	return "";
}

int LogModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return log.size();
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() > log.size())
		return QVariant();

	LogEntry *entry = log[index.row()];
	switch(role)
	{
	case TypeRole:
		return QVariant(entry->type);
	case RecordRole:
		return QVariant(entry->msg);
	case FileRole:
		return QVariant(entry->file);
	case LineRole:
		return QVariant(entry->line);
	case FunctionRole:
		return QVariant(entry->function);
	case TypeNameRole:
		return QVariant(entry->typestring);
	}

	return QVariant();
}

QHash<int, QByteArray> LogModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[TypeRole] = "type";
	roles[RecordRole] = "record";
	roles[FileRole] = "file";
	roles[LineRole] = "line";
	roles[FunctionRole] = "func";
	return roles;
}

void LogModel::write(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
{
	beginInsertRows(QModelIndex(), log.size(), log.size());
	log << new LogEntry(fromType(type), ctx.file, ctx.function, msg, ctx.line, type);
	endInsertRows();

	if (log.size() > MAX_LOG_LINES)
	{
		beginRemoveRows(QModelIndex(), 0, 0);
		delete log[0];
		log.removeFirst();
		endRemoveRows();
	}
}

void LogModel::clear()
{
	beginRemoveRows(QModelIndex(), 0, log.size());
	foreach (LogEntry *entry, log)
		delete entry;
	log.clear();
	endRemoveRows();
}

namespace Logging
{
	namespace
	{
		LogModel model;
	}

	void messageHandler(QtMsgType type, const QMessageLogContext& ctx, const QString& msg)
	{
		model.write(type, ctx, msg);
	}

	void installMessageHandler()
	{
		qInstallMessageHandler(&messageHandler);
	}

	void removeMessageHandler()
	{
		qInstallMessageHandler(0);
	}


	LogModel* instance()
	{
		return &model;
	}
}
