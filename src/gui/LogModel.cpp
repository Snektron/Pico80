#include <iostream>
#include "gui/LogModel.h"
#include "core/Logger.h"

void LogModel::write(std::string line)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	log << QString(line.c_str());
	endInsertRows();

	if (log.size() > MAX_LOG_LINES)
	{
		beginRemoveRows(QModelIndex(), 0, 0);
		log.removeFirst();
		endRemoveRows();
	}
}

int LogModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent);
	return log.size();
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() >= rowCount())
		return QVariant();

	if (role == RecordRole)
		return log[index.row()];
	return QVariant();
}

QHash<int, QByteArray> LogModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[RecordRole] = "record";
	return roles;
}
