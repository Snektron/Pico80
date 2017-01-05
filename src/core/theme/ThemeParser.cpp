#include "core/theme/ThemeParser.h"
#include <QDebug>
#include <QColor>

#define IS_UPPER(c) ('A' <= (c) && c <= 'Z')
#define IS_LOWER(c) ('a' <= (c) && c <= 'z')
#define IS_NUMBER(c) ('0' <= (c) && c <= '9')
#define IS_LETTER(c) (IS_UPPER(c) || IS_LOWER(c) || (c) == '_')
#define IS_WHITESPACE(c) ((c) == ' ' || (c) == '\n' || (c) == '\t')

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

ThemeParser::ThemeParser(QString filename):
	file(filename),
	state(State::OK)
{
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		state = State::ERROR;
		qCritical() << "Failed to open theme file" << filename;
	}
}

QVariant ThemeParser::parse()
{
	if (state != State::OK)
		return QVariantMap();
	if (parseFile() != State::OK)
		qCritical() << "Syntax error in theme file";

	return root.toVariant();
}

State ThemeParser::getState()
{
	return state;
}

QString ThemeParser::dumpStack()
{
	QString msg = "";
	bool first = true;

	foreach(QString str, stack)
	{
		if (first)
			first = false;
		else
			msg.append(".");
		msg.append(str);
	}

	return msg;
}

State ThemeParser::error(QString message)
{
	qCritical() << "Theme error" << message;
	return State::ERROR;
}

int ThemeParser::peek()
{
	char c;
	if (file.getChar(&c))
		file.ungetChar(c);
	else
		return EOF;
	return c;
}

int ThemeParser::consume()
{
	char c;
	if(!file.getChar(&c))
		return EOF;
	return c;
}

void ThemeParser::skipWhiteSpace()
{
	char c = peek();
	while (IS_WHITESPACE(c))
	{
		consume();
		c = peek();
	}
}

State ThemeParser::setThemeValue(QColor value)
{
	MapNode *map = &root;

	for (int i = 0; i < stack.size() - 1; i++)
	{
		QString str = stack[i];
		Node *node = map->get(str);
		if (!node)
		{
			MapNode *newMap = new MapNode();
			map->set(str, newMap);
			map = newMap;
		}
		else if(!node->isMap())
			return error("Cannot overwrite theme key with group");
		else
			map = static_cast<MapNode*>(node);
	}

	QString str = stack.top();
	Node *node = map->get(str);
	if (node && node->isMap())
		return error("Cannot overwrite theme group with key");
	else
		map->set(str, new VariantNode(value));

	return State::OK;
}

State ThemeParser::parseFile()
{
	skipWhiteSpace();
	while (peek() != EOF)
	{
		if (parseBody() != State::OK)
			return State::ERROR;
		skipWhiteSpace();
	}

	return State::OK;
}

State ThemeParser::parseBody()
{
	skipWhiteSpace();
	if (parseIdentifier() != State::OK)
		return State::ERROR;

	State res = State::OK;
	skipWhiteSpace();
	switch(peek())
	{
	case '{':
		consume();
		res = parseBlock();
		break;
	case '.':
		consume();
		res = parseBody();
		break;
	case '=':
		consume();
		res = parseAssignment();
		break;
	default:
		res = State::ERROR;
		break;
	}

	stack.pop();
	return res;
}

State ThemeParser::parseBlock()
{
	skipWhiteSpace();
	while (peek() != '}')
	{
		if (parseBody() != State::OK)
			return error("Block end ('}') expected");
		skipWhiteSpace();
	}
	consume();

	return State::OK;
}

State ThemeParser::parseAssignment()
{
	skipWhiteSpace();
	char c = peek();
	if (c != '#')
		return error("Color value does not start with a '#'");
	consume();

	int nibbles[6];

	for (int i = 0; i < 6; i++)
	{
		char n = peek();
		if ('a' <= n && n <= 'f')
			nibbles[i] = n - 'a' + 10;
		else if ('A' <= n && n <= 'F')
			nibbles[i] = n - 'A' + 10;
		else if ('0' <= n && n <= '9')
			nibbles[i] = n - '0';
		else
			return error("Error parsing theme color value");
		consume();
	}

	QColor color(nibbles[0] << 4 | nibbles[1],
				 nibbles[2] << 4 | nibbles[3],
				 nibbles[4] << 4 | nibbles[5]);

	return setThemeValue(color);
}

State ThemeParser::parseIdentifier()
{
	QString id = "";
	char c = peek();
	if (!IS_LETTER(c))
		return error("Identifier does not start with a letter");
	id.append(consume());

	c = peek();
	while(IS_LETTER(c) || IS_NUMBER(c))
	{
		id.append(consume());
		c = peek();
	}

	stack.push(id);
	return State::OK;
}
