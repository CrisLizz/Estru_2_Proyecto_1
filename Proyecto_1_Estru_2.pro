QT += core gui widgets multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arte.cpp \
    batalla.cpp \
    ciencia.cpp \
    cuestionario.cpp \
    descartes_lab.cpp \
    hallway.cpp \
    hearts.cpp \
    history.cpp \
    inventory.cpp \
    kant_class.cpp \
    main.cpp \
    mainwindow.cpp \
    mapa.cpp \
    menu.cpp \
    npcs.cpp \
    player.cpp \
    politics.cpp \
    protagonista.cpp \
    ruleta.cpp \
    trophies.cpp

HEADERS += \
    aristas.h \
    arte.h \
    batalla.h \
    ciencia.h \
    cuestionario.h \
    descartes_lab.h \
    hallway.h \
    hearts.h \
    history.h \
    inventory.h \
    kant_class.h \
    mainwindow.h \
    mapa.h \
    menu.h \
    nodo.h \
    npcs.h \
    player.h \
    politics.h \
    protagonista.h \
    ruleta.h \
    trophies.h \
    videowindow.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Deco.qrc \
    Fondos.qrc \
    Music.qrc \
    Npc.qrc \
    protagonista.qrc

DISTFILES +=
