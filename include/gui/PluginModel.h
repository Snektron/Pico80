#ifndef PLUGINMODEL_H
#define PLUGINMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include "core/PluginManager.h"

class PluginModel : public QAbstractListModel
{
	Q_OBJECT
private:
	PluginManager *manager;
	QList<PluginDescriptor> plugins;

public:
	enum PluginModelRoles
	{
		NameRole = Qt::UserRole + 1,
		FileRole
	};

	PluginModel(PluginManager *manager);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QHash<int, QByteArray> roleNames() const;
	Q_INVOKABLE void update();
	Q_INVOKABLE QVariant fileForPlugin(int index);
};

#endif // PLUGINMODEL_H
