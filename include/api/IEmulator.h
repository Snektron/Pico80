#ifndef EMULATOR_H
#define EMULATOR_H

#include <cstdint>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class IEmulator
{
public:
	virtual void tick();
	virtual ~IEmulator() = default;
public slots:
	virtual void onTurnedOn();
	virtual void onKeyPress(QKeyEvent *event);
	virtual void onKeyRelease(QKeyEvent *event);
	virtual void onMousePress(QMouseEvent *event);
	virtual void onMouseRelease(QMouseEvent *event);
	virtual void onMouseMove(QHoverEvent *event);
};

#endif // EMULATOR_H
