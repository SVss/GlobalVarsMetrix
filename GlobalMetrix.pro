TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    cleaner.cpp \
    file_work.cpp \
    counter.cpp \
    regexes.cpp

HEADERS += \
    regexes.h \
    file_work.h \
    stuff.h

