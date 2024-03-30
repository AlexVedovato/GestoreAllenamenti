#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFileDialog>

#include "../Allenamento.h"
#include "../CSV/GestoreCSV.h"

namespace View {

class MainWindow: public QMainWindow {
    Q_OBJECT

  private:
    bool has_unsaved_changes;
    Allenamento& allenamento;
    GestoreCSV csv;
    QToolBar* toolbar;

    void creaLabelIniziale();

  public:
    explicit MainWindow(Allenamento&, QWidget* =nullptr);
    void changesHappened();

  public slots:
    void nuovoAllenamento();
    void apriAllenamento();
    void salvaAllenamento();
    void salvaAllenamentoConNome();
    void toggleToolbar();
    void mostraStato(QString messaggio);
    void chiudi();
};

}

#endif
