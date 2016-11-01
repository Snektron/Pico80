#ifndef INCLUDE_PICO80_H_
#define INCLUDE_PICO80_H_

#include "core/Time.h"
#include "emu/Asic.h"

class Pico80 : Time::Timer
{
private:
	std::shared_ptr<Asic> asic;

public:
	Pico80();
	void run();
	bool trigger();
	~Pico80();
};

#endif /* INCLUDE_PICO80_H_ */
