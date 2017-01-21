#include "core/theme/Theme.h"
#include "core/theme/ThemeParser.h"

Theme::Theme():
	root(new MapNode())
{
	addFile(":/theme/default.thm");
}

Theme::~Theme()
{
	delete root;
}

void Theme::addFile(QString filename)
{
	ThemeParser parser(root, filename);
	parser.parse();
	emit themeChanged();
}

QVariant Theme::toVariant()
{
	return root->toVariant();
}
