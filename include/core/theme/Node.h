#ifndef NODE_H
#define NODE_H

#include <QVariant>
#include <QMap>
#include <QString>

class Node
{
public:
	virtual QVariant toVariant() = 0;
	virtual bool isMap() = 0;
	virtual ~Node() = default;
};

class VariantNode: public Node
{
private:
	QVariant variant;

public:
	VariantNode(QVariant variant);
	QVariant toVariant();
	bool isMap();
};

class MapNode: public Node
{
private:
	QMap<QString, Node*> children;

public:
	~MapNode();
	void set(QString key, Node *value);
	Node* get(QString key);
	QVariant toVariant();
	bool isMap();
};

#endif // NODE_H
