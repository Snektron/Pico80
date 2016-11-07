#ifndef INCLUDE_CORE_ENGINE_H_
#define INCLUDE_CORE_ENGINE_H_

#include "core/Application.h"
#include <memory>

namespace Engine
{
	void setApplication(std::shared_ptr<Application> application);
	void start();
	void stop();
	void resize(int width, int height);
}

#endif /* INCLUDE_CORE_ENGINE_H_ */
