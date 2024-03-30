#ifndef VIEW_MOSTRA_DIALOG_H
#define VIEW_MOSTRA_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>

#include "WidgetEsercizio.h"

#include "../EsercizioSerieTempo.h"
#include "../EsercizioSerieRipetizioni.h"

namespace View {

class MostraDialog: public QDialog {
  Q_OBJECT

  public:
    MostraDialog(Esercizio*, QDialog* = 0);
};

}

#endif