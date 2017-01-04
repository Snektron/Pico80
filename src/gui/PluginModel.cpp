#include "gui/PluginModel.h"

PluginModel::PluginModel(PluginManager *manager):
	manager(manager)
{
	update();
}

int PluginModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED(parent)
	return plugins.size();
}

QVariant PluginModel::data(const QModelIndex &index, int role) const
{
	if (index.row() < 0 || index.row() > plugins.size())
		return QVariant();

	PluginDescriptor descriptor = plugins[index.row()];
	switch(role)
	{
	case NameRole:
		return QVariant(descriptor.getPluginName());
	case FileRole:
		return QVariant(descriptor.getFileName());
	}

	return QVariant();
}

QHash<int, QByteArray> PluginModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[NameRole] = "name";
	roles[FileRole] = "file";
	return roles;
}

void PluginModel::update()
{
	beginRemoveRows(QModelIndex(), 0, plugins.size());
	plugins.clear();
	endRemoveRows();

	QList<PluginDescriptor> plugins = manager->availablePlugins();

	beginInsertRows(QModelIndex(), 0, plugins.size());
	this->plugins = plugins;
	endInsertRows();
}

QVariant PluginModel::fileForPlugin(int index)
{
	if (index < 0 || index > plugins.size())
		return QVariant();
	return QVariant(plugins[index].getFileName());
}
