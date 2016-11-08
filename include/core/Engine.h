#ifndef INCLUDE_CORE_ENGINE_H_
#define INCLUDE_CORE_ENGINE_H_

#include <memory>
#include "core/Application.h"
#include "core/Event.h"

namespace Engine
{
	void setApplication(std::shared_ptr<Application> application);
	void start();
	void stop();
	void resize(int width, int height);
	void mouseEvent(MouseEvent& event);
	void keyEvent(KeyEvent& event);
}

#endif /* INCLUDE_CORE_ENGINE_H_ */
