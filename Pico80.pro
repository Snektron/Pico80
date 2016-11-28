TEMPLATE = app

QT += qml quick gui opengl
CONFIG += c++11 silent
QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-reorder -Wno-extra

SOURCES += src/main.cpp \
    src/z80e/core/cpu.c \
    src/z80e/core/registers.c \
    src/core/Time.cpp \
    src/emu/device/Keyboard.cpp \
    src/emu/device/Mouse.cpp \
    src/emu/device/Screen.cpp \
    src/emu/interrupt/Interrupt.cpp \
    src/emu/memory/Memory.cpp \
    src/emu/memory/PageManager.cpp \
    src/emu/Asic.cpp \
    src/Settings.cpp \
    src/core/Logger.cpp \
    src/gui/DisplayRenderer.cpp \
    src/emu/AsicThread.cpp \
    src/Pico80.cpp \
    src/gui/Display.cpp \
    src/emu/Keys.cpp

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
    include/emu/device/Clock.h \
    include/emu/device/Keyboard.h \
    include/emu/device/Log.h \
    include/emu/device/Mouse.h \
    include/emu/device/Screen.h \
    include/emu/device/StorageController.h \
    include/emu/interrupt/Interrupt.h \
    include/emu/interrupt/TimerInt.h \
    include/emu/memory/Memory.h \
    include/emu/memory/MemoryBank.h \
    include/emu/memory/Page.h \
    include/emu/memory/PageManager.h \
    include/emu/Asic.h \
    include/emu/AsicThread.h \
    include/emu/Keys.h \
    include/emu/Platform.h \
    include/emu/TIKeys.h \
    include/core/Logger.h \
    include/core/Time.h \
    include/gui/Display.h \
    include/gui/DisplayRenderer.h \
    include/Pico80.h \
    include/Settings.h \

DISTFILES +=
