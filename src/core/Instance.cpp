#include "core/Instance.h"
#include "core/Logger.h"

#define TAG "Instance"

Instance::Instance(IPlugin *plugin):
	plugin(plugin)
{

}

IPlugin* Instance::getPlugin()
{
	return plugin;
}

Instance::~Instance()
{

}
