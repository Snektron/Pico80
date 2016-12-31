#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <string>
#include <QAbstractListModel>
#include <QVariant>
#include <qlogging.h>

#define MAX_LOG_LINES 500

class LogEntry
{
public:
	const QString typestring, file, function, msg;
	const int line, type;

	LogEntry(const QString& typestring, const QString& file,
			 const QString& function, const QString& msg,
			 const int line, const int type):
		typestring(typestring), file(file),
		function(function), msg(msg),
		line(line), type(type)
	{}
};

class LogModel : public QAbstractListModel
{
	Q_OBJECT
private:
	QList<LogEntry*> log;
public:
	enum LogRoles
	{
		TypeRole = Qt::UserRole + 1,
		RecordRole,
		FileRole,
		LineRole,
		FunctionRole,
		TypeNameRole
	};

	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;

public slots:
	void write(QtMsgType type, const QMessageLogContext& ctx, const QString& msg);
	void clear();
};

namespace Logging
{
	LogModel* instance();
	void installMessageHandler();
	void removeMessageHandler();
}

#endif // LOGMODEL_H
