#ifndef VIEW_AGGIUNGI_DIALOG_H
#define VIEW_AGGIUNGI_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QMessageBox>
#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QLineEdit>
#include <QIntValidator>

#include "WidgetEsercizio.h"

#include "../EsercizioSerieTempo.h"
#include "../EsercizioSerieRipetizioni.h"
#include "../Allenamento.h"
#include "../CSV/GestoreCSV.h"

namespace View {

class AggiungiDialog: public QDialog {
  Q_OBJECT

  private:
    Esercizio*& esercizio;
    unsigned int& posizione; 
    Allenamento lista_esercizi;

    WidgetEsercizio* widgetEsercizio;
    QLineEdit* input_posizione;

  public:
    AggiungiDialog(Esercizio*&,unsigned int&, QDialog* = 0);
  
  public slots:
    void gestisciInput();
};

}

#endif