#ifndef EMULATOR_H
#define EMULATOR_H

#include "emu/api/AbstractAsic.h"
#include "emu/api/AbstractDisplay.h"

class AbstractEmulator
{
public:
	AbstractAsic* createAsic();
	AbstractDisplayRenderer* createDisplayRenderer();
	virtual ~AbstractEmulator() = default;
};

#endif // EMULATOR_H
