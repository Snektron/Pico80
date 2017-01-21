#ifndef ITHEME_H
#define ITHEME_H

class ITheme
{
public:
	virtual void addFile(QString filename) = 0;
	virtual ~ITheme() = default;
};

#endif // ITHEME_H
