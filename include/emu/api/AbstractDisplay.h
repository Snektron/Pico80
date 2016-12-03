#ifndef RENDERER_H
#define RENDERER_H

class AbstractDisplayData
{
public:
	virtual ~AbstractDisplayData() = default;
};

class AbstractDisplayRenderer
{
public:
	virtual ~AbstractDisplayRenderer() = default;
public slots:
	virtual void synchronize(AbstractDisplayData *displayData) {}
	virtual void render() = 0;
};

#endif // RENDERER_H
