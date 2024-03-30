#ifndef VIEW_WIDGET_PRINCIPALE_H
#define VIEW_WIDGET_PRINCIPALE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QHeaderView>

#include "MainWindow.h"
#include "AggiungiDialog.h"
#include "ModificaDialog.h"
#include "MostraDialog.h"
#include "../EsercizioSerieTempo.h"
#include "../EsercizioSerieRipetizioni.h"
#include "../Allenamento.h"

namespace View {

class WidgetPrincipale: public QWidget {
  Q_OBJECT

  private:
    Allenamento& allenamento;
    MainWindow* mainWindow;
    QTableWidget* tableWidget;
    QPushButton* modifica;
    QPushButton* elimina;

    void aggiungiRigaEsercizio(const Esercizio&, unsigned int);
    void modificaRigaEsercizio(const Esercizio&, unsigned int);

  public:
    WidgetPrincipale(Allenamento&, MainWindow*, QWidget* = 0);
  
  public slots:
    void mostraEsercizio();
    void aggiungiEsercizio();
    void modificaEsercizio();
    void eliminaEsercizio();
};

}

#endif