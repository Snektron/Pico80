TEMPLATE = app

QT += qml quick gui opengl quickcontrols2
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra
INCLUDEPATH += include ../picore/include
QML_IMPORT_PATH += ../picore/qml/import

SOURCES += \
    src/main.cpp \
    src/core/PluginManager.cpp \
    src/emu/EmulatorThread.cpp \
    src/Pico80.cpp \
    src/Settings.cpp \
    src/gui/Logging.cpp \
    src/emu/EmulatorContext.cpp \
    src/core/PicoSettings.cpp \
    src/gui/PluginModel.cpp \
    src/core/System.cpp \
    src/core/theme/ThemeEngine.cpp \
    src/core/theme/ThemeParser.cpp

HEADERS += \
    include/core/PluginManager.h \
    include/emu/EmulatorThread.h \
    include/Pico80.h \
    include/Settings.h \
    include/gui/Logging.h \
    include/emu/EmulatorContext.h \
    include/core/QmlPicoEngine.h \
    include/core/PicoSettings.h \
    include/gui/PluginModel.h \
    include/core/System.h \
    include/core/theme/ThemeEngine.h \
    include/core/theme/ThemeParser.h

RESOURCES += \
    rsrc.qrc

win32: LIBS += -L../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ -lpicored
unix: LIBS += -L../build-Pico80-Desktop-Debug/ -lpicore

DISTFILES +=
