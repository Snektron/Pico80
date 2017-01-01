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

void Pico80::setEmulatorPlugin(QString file)
{
	delete emulator;
	IPlugin *plugin = manager->loadPluginByFile(file);
	if (plugin)
		qDebug() << "Activating plugin" << plugin->name();
	else
		qWarning() << "Failed to activate plugin" << file;

	emulator = new EmulatorContext(qmlEngine, plugin);
	emulator->start();
}

void Pico80::start()
{
	QList<PluginDescriptor> plugins = manager->availablePlugins();
	if (plugins.size() > 0)
		setEmulatorPlugin(plugins[0].getFileName());
	else
		setEmulatorPlugin("");
}

void Pico80::quit()
{
	qInfo() << "Stopping";
}
