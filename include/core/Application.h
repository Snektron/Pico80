#ifndef INCLUDE_CORE_APPLICATION_H_
#define INCLUDE_CORE_APPLICATION_H_

#include <stdexcept>
#include <string>
#include "core/Time.h"
#include "core/Event.h"

#ifndef MAX_FRAMESKIP
#define MAX_FRAMESKIP 5
#endif

#ifndef MAX_HANG
#define MAX_HANG 500000
#endif

typedef struct
{
	std::string name;
	int width, height;
} WindowConfig;

class Application
{
private:
	Time::nanoseconds fint, tint;
	WindowConfig wconf;
	bool running;

public:
	Application(int fps, int tps, WindowConfig wconf):
		fint(SECOND_IN_NANOS / fps),
		tint(SECOND_IN_NANOS / tps),
		wconf(wconf),
		running(false)
	{}

	virtual void onInitialize(){};
	virtual void onUpdate(){};
	virtual void onRender(){};
	virtual void onTerminate(){};
	virtual void onResize(int width, int height){};
	virtual void onMouseEvent(MouseEvent& event){};
	virtual void onKeyEvent(KeyEvent& event){};
	virtual void onError(const std::runtime_error& error){};

	virtual ~Application() = default;

	Time::nanoseconds getFrameInterval()
	{
		return fint;
	}

	Time::nanoseconds getTickInterval()
	{
		return tint;
	}

	WindowConfig getWindowConfig()
	{
		return wconf;
	}
};

#endif /* INCLUDE_CORE_APPLICATION_H_ */
