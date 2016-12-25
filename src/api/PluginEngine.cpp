#include "api/PluginEngine.h"

PluginEngine::PluginEngine():
	displayFactory(nullptr),
	emulatorFactory(nullptr)
{

}

PluginEngine::~PluginEngine()
{
	delete displayFactory;
	delete emulatorFactory;
}

template<typename T>
void PluginEngine::registerDisplay()
{
	delete displayFactory;
	displayFactory = new Factory<T>();
}

void PluginEngine::registerDisplayFactory(DisplayFactory *factory)
{
	delete displayFactory;
	displayFactory = factory;
}
