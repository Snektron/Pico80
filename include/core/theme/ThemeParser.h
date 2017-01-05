#ifndef THEMEPARSER_H
#define THEMEPARSER_H

#include <QVariantMap>
#include <QString>
#include <QFile>
#include <QStack>
#include <QMap>

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

enum class State
{
	OK,
	ERROR
};

class ThemeParser
{
private:
	QFile file;
	State state;
	QStack<QString> stack;
	MapNode root;

public:

	ThemeParser(QString filename);
	QVariant parse();
	State getState();
	QString dumpStack();

private:
	State error(QString message);
	int peek();
	int consume();
	void skipWhiteSpace();
	State setThemeValue(QColor value);

	State parseFile();
	State parseBody();
	State parseBlock();
	State parseAssignment();
	State parseIdentifier();
};

#endif // THEMEPARSER_H
