#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <string>
#include <QAbstractListModel>
#include <QVariant>

#define MAX_LOG_LINES 500

class LogModel : public QAbstractListModel
{
	Q_OBJECT
private:
	QStringList log;
public:
	enum LogRoles
	{
		RecordRole = Qt::UserRole + 1
	};

	void write(std::string line);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;
};

#endif // LOGMODEL_H
