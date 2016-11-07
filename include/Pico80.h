#ifndef INCLUDE_PICO80_H_
#define INCLUDE_PICO80_H_

#include <memory>
#include "core/Application.h"
#include "core/view/View.h"
#include "emu/EmulatorView.h"

#define FPS 60
#define TPS 1000

class Pico80 : public Application
{
private:
	ViewPtr root;
	std::shared_ptr<EmulatorView> emulator;

public:
	Pico80();
	void onInitialize();
	void onUpdate();
	void onRender();
	void onResize(int width, int height);
	void onError(const std::runtime_error& error);
};

#endif /* INCLUDE_PICO80_H_ */
