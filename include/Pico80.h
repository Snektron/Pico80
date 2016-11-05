#ifndef INCLUDE_PICO80_H_
#define INCLUDE_PICO80_H_

#include "core/Application.h"
#include "core/Time.h"
#include "emu/Asic.h"

#define FPS 60
#define TPS 1000
#define ASIC_CLOCK MHZ(50)
#define ASIC_TIMER 200

class Pico80 : public Application
{
private:
	std::shared_ptr<Asic> asic;
	Time::point last;

public:
	Pico80();
	void onInitialize();
	void onUpdate();
	void onRender();
	void onTerminate();
	void onError(const std::runtime_error& error);
};

#endif /* INCLUDE_PICO80_H_ */
