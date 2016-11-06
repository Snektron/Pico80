#ifndef INCLUDE_CORE_APPLICATION_H_
#define INCLUDE_CORE_APPLICATION_H_

#include <stdexcept>
#include "core/Time.h"

#ifndef MAX_FRAMESKIP
#define MAX_FRAMESKIP 5
#endif

#ifndef MAX_HANG
#define MAX_HANG 500000
#endif

class Application
{
private:
	Time::nanoseconds fint, tint;
	bool running;

public:
	Application(int fps, int tps);

	virtual void onInitialize() = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	virtual void onTerminate() = 0;
	virtual void onError(const std::runtime_error& error) = 0;

	void start();
	void stop();

	virtual ~Application() = default;

private:
	void initialize();
	void loop();
	void terminate();
};

#endif /* INCLUDE_CORE_APPLICATION_H_ */
