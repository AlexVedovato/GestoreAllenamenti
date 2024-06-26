######################################################################
# Automatically generated by qmake (3.1) Mon Dec 26 22:28:08 2022
######################################################################

TEMPLATE = app
TARGET = GestoreAllenamenti
INCLUDEPATH += .
QT += widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Allenamento.h \
           Esercizio.h \
           EsercizioRipetizioni.h \
           EsercizioSerie.h \
           EsercizioSerieRipetizioni.h \
           EsercizioSerieTempo.h \
           EsercizioTempo.h \
           EsercizioVisitorInterface.h \
           CSV/GestoreCSV.h \
           View/AggiungiDialog.h \
           View/EsercizioInfoVisitor.h \
           View/MainWindow.h \
           View/ModificaDialog.h \
           View/MostraDialog.h \
           View/WidgetEsercizio.h \
           View/WidgetPrincipale.h
SOURCES += Allenamento.cpp \
           Esercizio.cpp \
           EsercizioRipetizioni.cpp \
           EsercizioSerie.cpp \
           EsercizioSerieRipetizioni.cpp \
           EsercizioSerieTempo.cpp \
           EsercizioTempo.cpp \
           main.cpp \
           CSV/GestoreCSV.cpp \
           View/AggiungiDialog.cpp \
           View/EsercizioInfoVisitor.cpp \
           View/MainWindow.cpp \
           View/ModificaDialog.cpp \
           View/MostraDialog.cpp \
           View/WidgetEsercizio.cpp \
           View/WidgetPrincipale.cpp
RESOURCES += resources.qrc
