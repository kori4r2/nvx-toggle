TEMPLATE = app
TARGET = nvx-toggle

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets KAuth

SOURCES += \
    actionhelper.cpp \
    main.cpp \
    window.cpp

HEADERS += \
    actionhelper.h \
    window.h
