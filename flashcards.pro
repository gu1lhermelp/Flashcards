######################################################################
# Automatically generated by qmake (3.1) Tue Jul 24 08:04:20 2018
######################################################################

TEMPLATE = app
TARGET = flashcards
INCLUDEPATH += .

CONFIG += debug

# Input
HEADERS +=
SOURCES += main.cpp

include(dialogs/dialogs.pri)
include(widgets/widgets.pri)
include(windows/windows.pri)

DESTDIR = build
OBJECTS_DIR = build/.obj

QT += widgets sql
