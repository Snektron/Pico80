TEMPLATE = app

QT += qml quick gui opengl
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra

SOURCES += src/main.cpp \
    src/z80e/core/cpu.c \
    src/z80e/core/registers.c \
    src/core/Time.cpp \
    src/emu/pico80/device/Keyboard.cpp \
    src/emu/pico80/device/Mouse.cpp \
    src/emu/pico80/device/Screen.cpp \
    src/emu/pico80/interrupt/Interrupt.cpp \
    src/emu/pico80/memory/Memory.cpp \
    src/emu/pico80/memory/PageManager.cpp \
    src/emu/pico80/Asic.cpp \
    src/Settings.cpp \
    src/core/Logger.cpp \
    src/gui/DisplayRenderer.cpp \
    src/emu/AsicThread.cpp \
    src/Pico80.cpp \
    src/gui/Display.cpp \
    src/emu/pico80/Keys.cpp \
    src/gui/LogModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += include

HEADERS += \
    include/z80e/core/cpu.h \
    include/z80e/core/Device.h \
    include/z80e/core/Interrupt.h \
    include/z80e/core/Memory.h \
    include/z80e/core/registers.h \
    include/z80e/z80e.h \
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
    include/emu/AsicThread.h \
    include/emu/pico80/Keys.h \
    include/emu/pico80/Platform.h \
    include/emu/pico80/TIKeys.h \
    include/core/Logger.h \
    include/core/Time.h \
    include/gui/Display.h \
    include/gui/DisplayRenderer.h \
    include/Pico80.h \
    include/Settings.h \
    include/gui/LogViewPolicy.h \
    include/gui/LogModel.h \
    include/emu/pico80/Asic.h \
    include/emu/api/AbstractAsic.h \
    include/emu/api/AbstractDisplay.h \
    include/emu/api/AbstractEmulator.h

DISTFILES +=
