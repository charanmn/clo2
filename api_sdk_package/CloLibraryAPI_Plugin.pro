message("CloLibraryAPI_Plugin.pro build start")

build-debug {
	BUILD_DIR		= $$PWD/mac_release/CloLibraryAPI_Plugin/build
	BUILD_HOME_PATH = $$PWD
	MAC_RELEASE_PATH = $$PWD/mac_release
}

build-release {
	BUILD_DIR		= build
	BUILD_HOME_PATH = ../..
	MAC_RELEASE_PATH = ..
}

TARGET		= CloLibraryAPI_Plugin
TEMPLATE		= lib
DESTDIR		= $$BUILD_DIR
OBJECTS_DIR	= $$BUILD_DIR/object
MOC_DIR		= $$BUILD_DIR/moc
UI_DIR		= $$BUILD_DIR/ui
RCC_DIR		= $$BUILD_DIR/rcc

CONFIG		+= qt opengl cocoa x86_64 framework thread
CONFIG 		+= silent

DEFINES		+= CLO_API_INTERFACE_STATIC_BUILD

INCLUDEPATH += . \
	CLOAPIInterface \
	CLOAPIInterface/Lib \
	CLOAPIInterface/Samples/LibraryWindowImplementation \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes 

LIBS += ../../CLOAPIInterface/Lib/libCLOAPIInterface.dylib

FORMS += CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISearchDialogSample.ui \
		CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISignInDialogSample.ui \
		CLOAPIInterface/Samples/LibraryWindowImplementation/classes/PLMSettingsSample.ui

HEADERS += CLOAPIInterface/LibraryWindowInterface.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/LibraryWindowImplPlugin.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISearchDialogSample.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISignInDialogSample.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/PLMSettingDataSample.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/PLMSettingsSample.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APIStorage.h \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APIUtility.h 

SOURCES += CLOAPIInterface/Samples/LibraryWindowImplementation/LibraryWindowImplPlugin.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISearchDialogSample.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APISignInDialogSample.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/PLMSettingDataSample.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/PLMSettingsSample.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APIStorage.cpp \
	CLOAPIInterface/Samples/LibraryWindowImplementation/classes/APIUtility.cpp 

RESOURCES = CLOAPIInterface/Samples/LibraryWindowImplementation/classes/CLOFormat.qrc

# Disable Warnings
QMAKE_CFLAGS += -w
QMAKE_CXXFLAGS += -w

# Essential Options
QMAKE_CFLAGS += -fno-builtin-function -fno-inline -finput-charset=UTF-8
QMAKE_CXXFLAGS += -fno-builtin-function -fno-inline -finput-charset=UTF-8

# C++ only
QMAKE_CXXFLAGS += -fpermissive

CONFIG += c++11

QMAKE_MACOSX_DEPLOYMENT_TARGET	= 10.9
QMAKE_CXXFLAGS					+= -mmacosx-version-min=10.9
QMAKE_LFLAGS						+= -mmacosx-version-min=10.9

QMAKE_CFLAGS_X86_64		-=  -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5 
QMAKE_CXXFLAGS_X86_64	-=  -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5 
QMAKE_LFLAGS_X86_64		-=  -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5

QMAKE_LFLAGS		+= -stdlib=libc++ 
QMAKE_CXXFLAGS	+= -stdlib=libc++ -std=c++11

QMAKE_CC		= /Applications/Xcode.app/Contents/Developer/usr/bin/gcc
QMAKE_CXX	= /Applications/Xcode.app/Contents/Developer/usr/bin/g++

QMAKE_CFLAGS		+= -ferror-limit=0
QMAKE_CXXFLAGS	+= -ferror-limit=0
	
LIBS += -framework QtCore -framework AGL -framework Cocoa
QT	+= core

INCLUDEPATH += . \
	/System/Library/Frameworks
#	/usr/include

LIBS += 	-L/usr/lib

message("CloLibraryAPI_Plugin.pro compiler path...")
message($$QMAKE_CC)
message($$QMAKE_CXX)


