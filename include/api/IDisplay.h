#ifndef IDISPLAY_H
#define IDISPLAY_H

class IDisplay
{
public:
	virtual void render() = 0;
	virtual ~IDisplay() = default;
};

#endif // IDISPLAY_H
