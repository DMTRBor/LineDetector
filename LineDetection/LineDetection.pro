TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        calcinverse.cpp \
        main.cpp \
        ransac.cpp

HEADERS += \
    calcinverse.h \
    ransac.h
