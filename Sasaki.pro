QT += widgets webenginewidgets webenginecore

INCLUDEPATH += include

DESTDIR = ../bin

SOURCES += \
    src/History.cpp \
    src/Main.cpp \
    src/Sasaki.cpp \
    src/Settings.cpp \
    src/Star.cpp \
    src/StatusBar.cpp \
    src/WebView.cpp

HEADERS += \
    include/History.h \
    include/Sasaki.h \
    include/Settings.h \
    include/Star.h \
    include/StatusBar.h \
    include/WebView.h
