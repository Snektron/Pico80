#include "core/theme/Node.h"

VariantNode::VariantNode(QVariant variant):
	variant(variant)
{}

QVariant VariantNode::toVariant()
{
	return variant;
}

bool VariantNode::isMap()
{
	return false;
}

MapNode::~MapNode()
{
	QMapIterator<QString, Node*> i(children);
	while (i.hasNext())
	{
		i.next();
		delete i.value();
	}
}

void MapNode::set(QString key, Node *value)
{
	if (children.contains(key))
		delete children[key];
	children[key] = value;
}

Node* MapNode::get(QString key)
{
	if (!children.contains(key))
		return Q_NULLPTR;
	return children[key];
}

QVariant MapNode::toVariant()
{
	QVariantMap map;

	QMapIterator<QString, Node*> i(children);
	while (i.hasNext())
	{
		i.next();
		map[i.key()] = i.value()->toVariant();
	}
	return map;
}

bool MapNode::isMap()
{
	return true;
}
