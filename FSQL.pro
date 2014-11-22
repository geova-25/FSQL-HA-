TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fsql_manager.cpp \
    register.cpp \
    filemanager.cpp \
    registermanager.cpp \
    arbol_b.cpp \
    clave.cpp \
    nodoarbolb.cpp \
    interpreteserver.cpp \
    clientsocket.cpp \
    serversocket.cpp \
    socket.cpp \
    listacircular.cpp \
    interprete_client.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    fsql_manager.h \
    register.h \
    filemanager.h \
    vectorrelacional.h \
    nodorelacional.h \
    registermanager.h \
    vector3d.h \
    nodo3d.h \
    arbol_b.h \
    clave.h \
    nodoarbolb.h \
    interpreteserver.h \
    clientsocket.h \
    serversocket.h \
    socket.h \
    SocketException.h \
    interprete_client.h \
    listacircular.h

