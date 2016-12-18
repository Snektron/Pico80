#ifndef ASIC_H
#define ASIC_H

#include <cstdint>
#include <QObject>
#include "emu/api/AbstractDisplay.h"

class AbstractAsic : public QObject
{
	Q_OBJECT
public:
	virtual void tick(int cycles){}
	virtual bool isDisplayDirty() { return false; }
	virtual AbstractDisplayData* getDisplayData() { return nullptr; }
	virtual ~AbstractAsic() = default;
public slots:
	virtual void turnOn() {}
	virtual void keyPress(uint8_t key) {}
	virtual void keyRelease(uint8_t key) {}
	virtual void mousePress(uint8_t button) {}
	virtual void mouseRelease(uint8_t button) {}
	virtual void mouseMove(uint8_t x, uint8_t y) {}
};

#endif // ASIC_H
