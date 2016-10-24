#ifndef INCLUDE_PICO80_H_
#define INCLUDE_PICO80_H_

#include "core/Time.h"
#include "emu/Asic.h"

namespace Pico80
{
	bool parse_args(int argc, char* argv[]);
	void init();
	void start();
	void trigger();
	void destroy();
}

#endif /* INCLUDE_PICO80_H_ */
