#per test
#QT += core gui testlib
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += modello \
               modello/Filtri


SOURCES += \
    main.cpp \
    #test_modello.cpp \
    gui/mainwindow.cpp \
    modello/Filtri/filtroanno.cpp \
    modello/Filtri/filtrocompletate.cpp \
    modello/Filtri/filtrocongiuntivo.cpp \
    modello/Filtri/filtrodata.cpp \
    modello/Filtri/filtromeseanno.cpp \
    modello/Filtri/filtronome.cpp \
    modello/Filtri/filtropriorita.cpp \
    modello/Filtri/filtrotag.cpp \
    modello/Filtri/filtrotipo.cpp \
    modello/appuntamento.cpp \
    modello/attivita.cpp \
    modello/esame.cpp \
    modello/gestore.cpp \
    modello/jsonsavervisitor.cpp \
    modello/libretto.cpp \
    modello/scadenza.cpp \
    modello/sport.cpp

HEADERS += \
    gui/mainwindow.h \
    modello/Filtri/filtroanno.h \
    modello/Filtri/filtrocompletate.h \
    modello/Filtri/filtrocongiuntivo.h \
    modello/Filtri/filtrodata.h \
    modello/Filtri/filtromeseanno.h \
    modello/Filtri/filtronome.h \
    modello/Filtri/filtropriorita.h \
    modello/Filtri/filtrotag.h \
    modello/Filtri/filtrotipo.h \
    modello/Filtri/abstractfilter.h \
    modello/activityvisitorinterface.h \
    modello/appuntamento.h \
    modello/attivita.h \
    modello/constactivityvisitorinterface.h \
    modello/esame.h \
    modello/gestore.h \
    modello/jsonsavervisitor.h \
    modello/libretto.h \
    modello/scadenza.h \
    modello/sport.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
#workaroun che ho dovuto aggiungere per un problema di incompatibilità con clang di apple sui processopri arm
QMAKE_CXXFLAGS += -Wno-error=implicit-function-declaration
QMAKE_CXXFLAGS += -Wno-implicit-function-declaration
