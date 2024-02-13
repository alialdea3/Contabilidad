TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-bibliotecacontabilidad-Desktop-Release/release/ -lbibliotecacontabilidad
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-bibliotecacontabilidad-Desktop-Release/debug/ -lbibliotecacontabilidad
else:unix: LIBS += -L$$PWD/../build-bibliotecacontabilidad-Desktop-Release/ -lbibliotecacontabilidad

INCLUDEPATH += $$PWD/../bibliotecacontabilidad
DEPENDPATH += $$PWD/../bibliotecacontabilidad

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-bibliotecacontabilidad-Desktop-Release/release/libbibliotecacontabilidad.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-bibliotecacontabilidad-Desktop-Release/debug/libbibliotecacontabilidad.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-bibliotecacontabilidad-Desktop-Release/release/bibliotecacontabilidad.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-bibliotecacontabilidad-Desktop-Release/debug/bibliotecacontabilidad.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-bibliotecacontabilidad-Desktop-Release/libbibliotecacontabilidad.a
