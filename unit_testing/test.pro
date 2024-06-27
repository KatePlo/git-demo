QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS +=  ../nod/nod.h
SOURCES +=  tst_test.cpp
