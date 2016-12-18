TEMPLATE = app

QT += qml quick gui opengl
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra

SOURCES += \
    src/main.cpp \
    src/core/Logger.cpp \
    src/core/Time.cpp \
    src/core/PluginManager.cpp \
    src/core/Instance.cpp \
    src/emu/EmulatorThread.cpp \
    src/gui/display/DisplayRenderer.cpp \
    src/gui/display/Display.cpp \
    src/gui/LogModel.cpp \
    src/Pico80.cpp \
    src/Settings.cpp \
    src/gui/display/FallbackDisplay.cpp

RESOURCES += qml.qrc

INCLUDEPATH += include

HEADERS += \
    include/api/IEmulator.h \
    include/api/IPlugin.h \
    include/api/IDisplay.h \
    include/core/Logger.h \
    include/core/Time.h \
    include/core/PluginManager.h \
    include/core/Instance.h \
    include/emu/EmulatorThread.h \
    include/gui/display/Display.h \
    include/gui/display/DisplayRenderer.h \
    include/gui/LogViewPolicy.h \
    include/gui/LogModel.h \
    include/Pico80.h \
    include/Settings.h \
    include/gui/display/FallbackDisplay.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
