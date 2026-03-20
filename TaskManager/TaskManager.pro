QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    gui/mainwindow.cpp \
    modello/appuntamento.cpp \
    modello/attivita.cpp \
    modello/esame.cpp \
    modello/scadenza.cpp \
    modello/sport.cpp

HEADERS += \
    gui/mainwindow.h \
    modello/activityvisitorinterface.h \
    modello/appuntamento.h \
    modello/attivita.h \
    modello/constactivityvisitorinterface.h \
    modello/esame.h \
    modello/scadenza.h \
    modello/sport.h

FORMS += \
    gui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
