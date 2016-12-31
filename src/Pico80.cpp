#include "Pico80.h"
#include <QQmlContext>
#include <picore/PluginEngine.h>
#include "gui/Logging.h"

Pico80::Pico80():
	emulator(Q_NULLPTR)
{
	Logging::installMessageHandler();
	qInfo() << "Starting";
	theme = new ThemeEngine();
	manager = new PluginManager();

	QQmlContext *ctx = qmlEngine.rootContext();
	ctx->setContextProperty("logModel", Logging::instance());
	ctx->setContextProperty("theme", theme->loadTheme());

	qmlEngine.load(QUrl("qrc:/qml/main.qml"));
}

Pico80::~Pico80()
{
	delete emulator;
	delete manager;
	delete theme;
	Logging::removeMessageHandler();
}

template <typename T>
T Pico80::findChild(QString name)
{
	foreach (QObject* rootObject, qmlEngine.rootObjects())
	{
		T object = rootObject->findChild<T>(name);
		if (object)
			return object;
	}

	return Q_NULLPTR;
}

void Pico80::setEmulatorPlugin(QString name)
{
	delete emulator;
	IPlugin *plugin = manager->getPlugin(name);
	if (plugin)
		qDebug() << "Activating plugin" << name;
	else
		qWarning() << "Failed to activate plugin" << name;

	emulator = new EmulatorContext(qmlEngine, plugin);
	emulator->start();
}

void Pico80::start()
{
	if (manager->hasPlugins())
		setEmulatorPlugin(manager->getPlugins()[0]->name());
	else
		setEmulatorPlugin("");
}

void Pico80::quit()
{
	qInfo() << "Stopping";
}
