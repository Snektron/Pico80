TEMPLATE = app

QT += qml quick gui opengl quickcontrols2
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra
INCLUDEPATH += include
QML_IMPORT_PATH += ../picore/qml/import

SOURCES += \
    src/main.cpp \
	src/core/PluginManager.cpp \
    src/Pico80.cpp \
	src/gui/Logging.cpp \
    src/core/PicoSettings.cpp \
    src/gui/PluginModel.cpp \
    src/core/theme/ThemeEngine.cpp \
    src/core/theme/ThemeParser.cpp \
    src/core/PicoQmlEngine.cpp \
    src/DefaultEmulatorContext.cpp \
    src/core/theme/Node.cpp \
    src/core/theme/Theme.cpp \
    src/core/PicoEngine.cpp \
    src/core/PicoQml.cpp

HEADERS += \
	include/core/PluginManager.h \
    include/Pico80.h \
	include/gui/Logging.h \
    include/core/PicoSettings.h \
    include/gui/PluginModel.h \
    include/core/theme/ThemeEngine.h \
    include/core/theme/ThemeParser.h \
    include/core/PicoQmlEngine.h \
    include/Pico80/api/IEmulatorContext.h \
    include/Pico80/api/IPlugin.h \
    include/Pico80/api/IPicoQmlEngine.h \
    include/DefaultEmulatorContext.h \
    include/core/theme/Node.h \
    include/core/theme/Theme.h \
    include/core/PicoEngine.h \
    include/core/PicoQml.h \
    include/Pico80/api/IPicoSettings.h \
    include/Pico80/api/IPicoEngine.h \
    include/Pico80/api/ITheme.h

RESOURCES += \
    rsrc.qrc

DISTFILES +=
