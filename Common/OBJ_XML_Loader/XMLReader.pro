#Project type
TEMPLATE = app

#Binary
TARGET = XML_OBJ_Reader


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
HEADERS += include/Mesh.hpp
HEADERS += include/Vertex.hpp
HEADERS += include/Point.hpp
HEADERS += include/Fonctions.hpp


#UIs
FORMS += 

#Ressources
RESOURCES = 

#Sources
SOURCES += source/main.cpp
SOURCES += source/Mesh.cpp
SOURCES += source/Vertex.cpp
SOURCES += source/Point.cpp
SOURCES += source/Fonctions.cpp

#extra targets
mytarget.target = run
mytarget.commands = make && ./$$DESTDIR/$$TARGET

QMAKE_EXTRA_TARGETS += mytarget
