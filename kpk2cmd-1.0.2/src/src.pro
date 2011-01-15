SOURCES =kpk2cmd.cpp \
kpk2cmdwidget.cpp \
main.cpp \
getfamilypart.cpp \
csList.cpp \
preferenceswidget.cpp \
preferencewidget.cpp

TARGET =../bin/kpk2cmd

TEMPLATE = app

HEADERS += kpk2cmd.h \
kpk2cmdwidget.h \
getfamilypart.h \
 csList.h \
 preferencewidget.h

INCLUDEPATH += /usr/include/qt3

LIBS += -L/usr/local/lib

FORMS += kpk2cmdwidgetbase.ui \
 preferencewidgetbase.ui

CONFIG += debug

IMAGES += spin1.png \
spin2.png \
spin3.png \
spin4.png \
spin5.png \
spin6.png \
spin7.png \
spin8.png \
 run.png \
 stop.png


CONFIG -= release

SOURCES -= csData.cpp \
 preferenceswidget.cpp

QMAKE_UIC = ./hack.sh
