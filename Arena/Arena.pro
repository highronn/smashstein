# Project type
TEMPLATE = app

# Binary
TARGET = Arena

# Sources dir
DEPENDPATH += . \
    source \
    source/UI

# Includes dirs
INCLUDEPATH += include/ \
    source/AUTOGEN \
    ../openkn-smashstein/include/ \
    ../fmod/

# Where to build
DESTDIR += bin

# QT additional config
CONFIG += qt \
    opengl \
    stl \
    exceptions \
    thread \
    warn_on \
    debug # debug_and_release
QMAKE_CXXFLAGS += -Wno-deprecated -std=c++11

# QT config
QT += core \
    xml \
    gui \
    opengl

# DISTFILES
DISTFILES += bin/

# Defines
DEFINES +=

# Added libs
LIBS += -ldl \
    -lm \
    -lGL \
    -lGLU \
    -lOpenKN-math

LIBS += -lfmodex \
    -lboost_graph

# Where to build MOCs
MOC_DIR = source/AUTOGEN

# Where to build .o
OBJECTS_DIR = source/.o

# Where to build .hpp from .ui
UI_DIR = source/AUTOGEN

# Where to build .cpp from .qrc
RCC_DIR = source/AUTOGEN/RSC/

# Headers
HEADERS += include/RTVector.hpp \
    include/RTMath.hpp \
    include/Application.hpp \
    include/anorms.hpp \
    include/Vertex.hpp \
    include/Point.hpp \
    include/BackTexture.hpp \
    include/Jump.hpp \
    include/Land.hpp \
    include/Shoot.hpp \
    include/MD2Model.hpp \
    include/RobotInfo.hpp \
    include/Return.hpp \
    include/Mesh.hpp \
    include/DecorMesh.hpp \
    include/Shoot2.hpp \
    include/main.hpp \
    include/StandUp.hpp \
    include/Victory.hpp \
    include/Damage.hpp \
    include/Throw.hpp \
    include/Edge.hpp \
    include/EdgeLengthMap.hpp \
    include/NodeBoundingBox.hpp \
    include/Fall.hpp \
    include/Run.hpp \
    include/StandBy.hpp \
    include/Death.hpp \
    include/NormalSpeaker.hpp \
    include/Node.hpp \
    include/IOMesh.hpp \
    include/RTColor.hpp \
    include/DoubleBillBoard.hpp \
    include/WorldBillBoard.hpp \
    include/RTPoint.hpp \
    include/Wrap.hpp \
    include/Robots.hpp \
    include/variables.hpp \
    include/FirePhysik.hpp \
    include/Particle.hpp \
    include/Projectiles.hpp \
    include/BillBoard.hpp \
    include/NoPhysik.hpp \
    include/SystemParticles.hpp \
    include/Animation.hpp \
    include/CocoNut.hpp \
    include/GLWidget.hpp \
    include/WaterPhysik.hpp \
    include/WaterBall.hpp \
    include/MainWindow.hpp \
    include/ExplodingCube.hpp \
    include/Shield.hpp \
    include/HitPhysik.hpp \
    include/Hit.hpp \
    include/EndPhysik.hpp \
    include/End.hpp \
    include/Fonctions.hpp \
    include/Arena.hpp \
    include/Sound.hpp \
    include/BoxmanState.hpp \
    include/Block.hpp \
    include/BoxmanRadarReport.hpp \
    include/Boxman.hpp \
    include/EffectFactory.hpp \
    include/FireBall.hpp

# UIs
FORMS += Ui_MainWindow.ui \
    Ui_DialogPreferences.ui \
	Ui_DialogKeyboard.ui \
	Ui_DialogAboutSmashtein.ui

# Ressources
RESOURCES =

# Sources
SOURCES += source/NormalSpeaker.cpp \
    source/Vertex.cpp \
    source/Application.cpp \
    source/Point.cpp \
    source/BackTexture.cpp \
    source/Land.cpp \
    source/MD2Model.cpp \
    source/Return.cpp \
    source/DecorMesh.cpp \
    source/Edge.cpp \
    source/Node.cpp \
    source/Damage.cpp \
    source/Throw.cpp \
    source/RobotInfo.cpp \
    source/Animation.cpp \
    source/Victory.cpp \
    source/StandUp.cpp \
    source/Mesh.cpp \
    source/Fall.cpp \
    source/IOMesh.cpp \
    source/StandBy.cpp \
    source/DoubleBillBoard.cpp \
    source/WorldBillBoard.cpp \
    source/SystemParticles.cpp \
    source/Particle.cpp \
    source/Projectiles.cpp \
    source/BillBoard.cpp \
    source/NoPhysik.cpp \
    source/main.cpp \
    source/Jump.cpp \
    source/GLWidget.cpp \
    source/Run.cpp \
    source/WaterBall.cpp \
    source/MainWindow.cpp \
    source/Robots.cpp \
    source/CocoNut.cpp \
    source/ExplodingCube.cpp \
    source/Death.cpp \
    source/Shoot.cpp \
    source/Shoot2.cpp \
    source/Shield.cpp \
    source/Hit.cpp \
    source/HitPhysik.cpp \
    source/EndPhysik.cpp \
    source/End.cpp \
    source/Fonctions.cpp \
    source/Sound.cpp \
    source/FirePhysik.cpp \
    source/WaterPhysik.cpp \
    source/BoxmanState.cpp \
    source/Boxman.cpp \
    source/Block.cpp \
    source/Arena.cpp \
    source/BoxmanRadarReport.cpp \
    source/EffectFactory.cpp \
    source/FireBall.cpp

# make run
myTarget.target = run
myTarget.commands = make -j3 && ./$$DESTDIR/$$TARGET
makeAIs.target = all
makeAIs.commands = (cd ../AIs/AINormal; qmake; make -f Makefile; cd ../AIFearful; qmake; make -f Makefile; cd ..; mv bin/*.so ../Arena/bots)
QMAKE_EXTRA_TARGETS += myTarget makeAIs
