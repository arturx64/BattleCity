#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T15:49:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testtest
CONFIG   += console
CONFIG   -= app_bundle

CONFIG   += c++11

TEMPLATE = app

INCLUDEPATH +=   ../../src/includes/

SOURCES += \
    phisical_engine_test.cpp \
    ../../src/src/Phisics/phisical_engine.cpp \
    ../../src/src/GameComponents/actor.cpp \
    ../../src/src/GameComponents/wall_actor.cpp \
    ../../src/src/Phisics/collider.cpp \
    channel_test.cpp \
    ../../src/src/Phisics/channel.cpp \
    ../../src/src/direction.cpp \
    main.cpp \
    ../../src/src/GameComponents/brick_wall.cpp \
    ../../src/src/Phisics/tabular_collider.cpp \
    ../../src/src/Phisics/hit_visitor.cpp \
    ../../src/src/Phisics/rect_collider.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/includes/GameComponents/actor.h \
    ../../src/includes/Phisics/phisical_engine.h \
    ../../src/includes/GameComponents/wall_actor.h \
    ../../src/includes/GameComponents/wall_type.h \
    ../../src/includes/Phisics/channel.h \
    ../../src/includes/Phisics/collider.h \
    channel_test.h \
    phisical_engine_test.h \
    ../../src/includes/GameComponents/brick_wall.h \
    ../../src/includes/Phisics/tabular_collider.h \
    ../../src/includes/Phisics/hit_visitor.h \
    ../../src/includes/Phisics/rect_collider.h
