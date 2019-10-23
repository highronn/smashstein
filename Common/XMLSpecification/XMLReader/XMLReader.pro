#Project type
TEMPLATE = app

#Binary
TARGET = XMLReader


#Sources dir
DEPENDPATH += source/

#Includes dirs
INCLUDEPATH += include ../../../openkn-smashstein/include/

#Where to build
DESTDIR = bin

#QT additional config
CONFIG+= qt plugin stl exceptions thread warn_on debug #debug_and_release

#QT config
QT += core
QT += xml

#DISTFILES
DISTFILES += bin

#Defines
DEFINES +=

#Added libs
LIBS += -lglut -lGL -lglui -lm -lOpenKN-math


#Where to build MOCs
MOC_DIR = source/AUTOGEN

#Where to build .o
OBJECTS_DIR = bin/

#Where to build .hpp from .ui
UI_DIR = source/AUTOGEN

#Where to build .cpp from .qrc
RCC_DIR = source/AUTOGEN/RSC/


#Headers
HEADERS += include/variables.hpp
HEADERS += include/main.hpp


#UIs
FORMS += 

#Ressources
RESOURCES = 

#Sources
SOURCES += source/main.cpp

#extra targets
mytarget.target = run
mytarget.commands = make && ./$$DESTDIR/$$TARGET

QMAKE_EXTRA_TARGETS += mytarget
