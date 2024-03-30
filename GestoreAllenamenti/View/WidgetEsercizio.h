#ifndef VIEW_WIDGET_ESERCIZIO_H
#define VIEW_WIDGET_ESERCIZIO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPainter>

#include "../EsercizioSerieTempo.h"
#include "../EsercizioSerieRipetizioni.h"
#include "EsercizioInfoVisitor.h"

namespace View {

class WidgetEsercizio: public QWidget {
  Q_OBJECT

  private:
    Esercizio*& esercizio;
    bool readonly;
    EsercizioInfoVisitor visitor;

    QTextEdit* nome;
    QTextEdit* descrizione;

  public:
    WidgetEsercizio(Esercizio*&, bool, QWidget* = 0);
    void gestisciInput();
};

}

#endif