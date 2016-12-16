TEMPLATE = app

QT += qml quick gui opengl
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra

SOURCES += \
    src/main.cpp \
    src/core/Logger.cpp \
    src/core/Time.cpp \
    src/emu/pico80/device/Keyboard.cpp \
    src/emu/pico80/device/Mouse.cpp \
    src/emu/pico80/device/Screen.cpp \
    src/emu/pico80/interrupt/Interrupt.cpp \
    src/emu/pico80/memory/Memory.cpp \
    src/emu/pico80/memory/PageManager.cpp \
    src/emu/pico80/Asic.cpp \
    src/emu/pico80/Keys.cpp \
    src/emu/EmulatorThread.cpp \
    src/gui/DisplayRenderer.cpp \
    src/gui/Display.cpp \
    src/gui/LogModel.cpp \
    src/z80e/core/cpu.c \
    src/z80e/core/registers.c \
    src/Pico80.cpp \
    src/Settings.cpp \
    src/core/PluginManager.cpp

RESOURCES += qml.qrc

INCLUDEPATH += include

HEADERS += \
    include/core/Logger.h \
    include/core/Time.h \
    include/emu/api/AbstractAsic.h \
    include/emu/api/AbstractDisplay.h \
    include/emu/api/AbstractEmulator.h \
    include/emu/pico80/device/Clock.h \
    include/emu/pico80/device/Keyboard.h \
    include/emu/pico80/device/Log.h \
    include/emu/pico80/device/Mouse.h \
    include/emu/pico80/device/Screen.h \
    include/emu/pico80/device/StorageController.h \
    include/emu/pico80/interrupt/Interrupt.h \
    include/emu/pico80/interrupt/TimerInt.h \
    include/emu/pico80/memory/Memory.h \
    include/emu/pico80/memory/MemoryBank.h \
    include/emu/pico80/memory/Page.h \
    include/emu/pico80/memory/PageManager.h \
    include/emu/pico80/Keys.h \
    include/emu/pico80/Platform.h \
    include/emu/pico80/TIKeys.h \
    include/emu/pico80/Asic.h \
    include/emu/EmulatorThread.h \
    include/gui/Display.h \
    include/gui/DisplayRenderer.h \
    include/gui/LogViewPolicy.h \
    include/gui/LogModel.h \
    include/z80e/core/cpu.h \
    include/z80e/core/Device.h \
    include/z80e/core/Interrupt.h \
    include/z80e/core/Memory.h \
    include/z80e/core/registers.h \
    include/z80e/z80e.h \
    include/Pico80.h \
    include/Settings.h \
    include/core/PluginManager.h \
    include/api/IEmulator.h \
    include/api/IPlugin.h \
    include/api/IDisplay.h

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
