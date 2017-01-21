#ifndef THEMEPARSER_H
#define THEMEPARSER_H

#include <QString>
#include <QFile>
#include <QStack>
#include "core/theme/Node.h"

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
	MapNode *root;

public:
	ThemeParser(MapNode *root, QString filename);
	void parse();
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
