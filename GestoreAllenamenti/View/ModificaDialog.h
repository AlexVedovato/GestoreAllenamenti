#ifndef VIEW_MODIFICA_DIALOG_H
#define VIEW_MODIFICA_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>

#include "WidgetEsercizio.h"

#include "../EsercizioSerieTempo.h"
#include "../EsercizioSerieRipetizioni.h"

namespace View {

class ModificaDialog: public QDialog {
  Q_OBJECT

  private:
    Esercizio*& esercizio;

    WidgetEsercizio* widgetEsercizio;

  public:
    ModificaDialog(Esercizio*&, QDialog* = 0);
  
  public slots:
    void gestisciInput();
};

}

#endif