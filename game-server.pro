#-------------------------------------------------
#
# Project created by QtCreator 2011-06-19T09:00:31
#
#-------------------------------------------------

QT       += core network sql testlib

QT       -= gui

TARGET = game-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    lib/Server.cpp \
    lib/Database.cpp \
    lib/User.cpp \
    lib/GameMap.cpp \
    lib/MapCell.cpp \
    lib/Npc.cpp \
    lib/Quest.cpp \
    lib/Mob.cpp \
    lib/Client.cpp \
    lib/Item.cpp \
    lib/Character.cpp

HEADERS += \
    lib/Server.h \
    lib/Database.h \
    lib/User.h \
    lib/GameMap.h \
    lib/MapCell.h \
    lib/Npc.h \
    lib/Quest.h \
    lib/Mob.h \
    lib/Client.h \
    lib/Item.h \
    lib/Character.h
