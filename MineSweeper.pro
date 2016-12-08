QT += widgets

TARGET = MineSweeper


SOURCES += main.cpp \
    gameboard.cpp \
    space.cpp \
    counter.cpp \
    icon.cpp \
    mainwindow.cpp

HEADERS += \
    gameboard.h \
    space.h \
    counter.h \
    icon.h \
    mainwindow.h

RESOURCES += \
    minesweeper.qrc

DISTFILES +=
