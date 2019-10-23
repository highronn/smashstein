#Project type
TEMPLATE = lib

#Binary
TARGET = AIFearful


#Sources dir
DEPENDPATH +=   . \
				../source \
				../../Arena/source/

#Includes dirs
INCLUDEPATH +=  ../source/ \
				../../openkn-smashstein/include/ \
				../../Arena/include/ \
				../../fmod/ \
				/usr/local/include

#Where to build
DESTDIR = ../bin/


#QT additional config
CONFIG+= qt plugin stl exceptions thread warn_on debug #debug_and_release

QMAKE_CXXFLAGS += -Wno-deprecated

#QT config
QT +=   core \
		xml

#DISTFILES
DISTFILES += ../bin/

#Defines
DEFINES +=

#Added libs
LIBS += -lOpenKN-math


#Where to build .o
OBJECTS_DIR = ../source/.o


#Headers
HEADERS += ../../Arena/include/BoxmanRadarReport.hpp \
		   Behavior.hpp \

#Ressources
RESOURCES =

#Sources
SOURCES +=  AIFearful.cpp \
			BoxmanRadarReport.cpp \
			Behavior.cpp \
