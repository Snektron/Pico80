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
    src/gui/display/DisplayRenderer.cpp \
    src/gui/display/Display.cpp \
    src/gui/display/FallbackDisplay.cpp \
    src/Pico80.cpp \
    src/Settings.cpp \
    src/gui/Logging.cpp \
    src/gui/display/DisplayWrapper.cpp \
    src/emu/EmulatorContext.cpp \
    src/gui/ThemeEngine.cpp \
    src/core/PicoSettings.cpp

HEADERS += \
    include/core/PluginManager.h \
    include/emu/EmulatorThread.h \
    include/gui/display/Display.h \
    include/gui/display/DisplayRenderer.h \
    include/gui/display/FallbackDisplay.h \
    include/Pico80.h \
    include/Settings.h \
    include/gui/Logging.h \
    include/gui/display/DisplayWrapper.h \
    include/emu/EmulatorContext.h \
    include/gui/ThemeEngine.h \
    include/core/QmlPicoEngine.h \
    include/core/PicoSettings.h

RESOURCES += \
    rsrc.qrc

win32: LIBS += -L../build-Pico80-Desktop_Qt_5_7_0_MinGW_32bit-Debug/ -lpicored
unix: LIBS += -L../build-Pico80-Desktop-Debug/ -lpicore

DISTFILES +=
