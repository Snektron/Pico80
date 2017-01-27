#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "Pico80.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
	QGuiApplication::setApplicationName("Pico80");
	QGuiApplication::setApplicationDisplayName("Pico80");
	QGuiApplication::setApplicationVersion("0");
	QGuiApplication::setOrganizationName("QuantumInfinity");
	QGuiApplication::setOrganizationDomain("quantuminfinity.space");

	Pico80 pico;
	QObject::connect(&app, SIGNAL(aboutToQuit()), &pico, SLOT(quit()));

    return app.exec();
}
