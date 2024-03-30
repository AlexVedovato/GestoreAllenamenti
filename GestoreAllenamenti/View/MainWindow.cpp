#include "MainWindow.h"
#include "WidgetPrincipale.h"

namespace View {

MainWindow::MainWindow(Allenamento& all, QWidget* parent) : QMainWindow(parent), has_unsaved_changes(false),
allenamento(all), csv("") {
    this->setWindowTitle(tr("IL TUO ALLENAMENTO"));
    
    QAction* nuovo = new QAction(
        QIcon(QPixmap((":/assets/icons/new.svg"))),
        "Nuovo"
    );
    nuovo->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    QAction* apri = new QAction(
        QIcon(QPixmap((":/assets/icons/open.svg"))),
        "Apri"
    );
    apri->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    QAction* salva = new QAction(
        QIcon(QPixmap((":/assets/icons/save.svg"))),
        "Salva"
    );
    salva->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
    QAction* salva_con_nome = new QAction(
        QIcon(QPixmap((":/assets/icons/save_as.svg"))),
        "Salva con nome"
    );
    salva_con_nome->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
    QAction* chiudi = new QAction(
        QIcon(QPixmap((":/assets/icons/close.svg"))),
        "Chiudi"
    );
    chiudi->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    QAction* togge_toolbar = new QAction(
        "Barra degli strumenti"
    );

    QMenu* file = menuBar()->addMenu("&File");
    file->addAction(nuovo);
    file->addAction(apri);
    file->addAction(salva);
    file->addAction(salva_con_nome);
    file->addSeparator();
    file->addAction(chiudi);
    QMenu* view = menuBar()->addMenu("&Visualizza");
    view->addAction(togge_toolbar);

    toolbar = addToolBar("File Toolbar");
    toolbar->addAction(nuovo);
    toolbar->addAction(apri);
    toolbar->addAction(salva);
    toolbar->addAction(salva_con_nome);
    toolbar->addSeparator();
    toolbar->addAction(chiudi);
    
    creaLabelIniziale();

    connect(nuovo, &QAction::triggered, this, &MainWindow::nuovoAllenamento);
    connect(apri, &QAction::triggered, this, &MainWindow::apriAllenamento);
    connect(salva, &QAction::triggered, this, &MainWindow::salvaAllenamento);
    connect(salva_con_nome, &QAction::triggered, this, &MainWindow::salvaAllenamentoConNome);
    connect(chiudi, &QAction::triggered, this, &MainWindow::chiudi);
    connect(togge_toolbar, &QAction::triggered, this, &MainWindow::toggleToolbar);

    mostraStato("Pronto!"); 
}

void MainWindow::creaLabelIniziale() {
    QLabel* label=new QLabel("Crea un nuovo allenamento oppure aprine uno già esistente!");
    label->setAlignment(Qt::AlignCenter);
    QFont font=label->font();
    font.setPointSize(16);
    label->setFont(font);
    label->setMinimumWidth(750);
    label->setMinimumHeight(250);
    QWidget* oldCentralWidget = takeCentralWidget();
    if(oldCentralWidget) {delete oldCentralWidget;}
    setCentralWidget(label);
}

void MainWindow::changesHappened() {
    has_unsaved_changes = true;
}

void MainWindow::nuovoAllenamento() {
    if (has_unsaved_changes) {
        QMessageBox msgBox; 
        msgBox.setWindowTitle(tr("Sei sicuro di non voler salvare l'allenamento corrente?"));
        msgBox.setText(tr("Ci sono delle modifiche non salvate, se creerai un nuovo allenamento queste andranno perse. Sei sicuro di voler continuare?")); 
        msgBox.addButton(tr("SI"), QMessageBox::YesRole); 
        QAbstractButton* no = msgBox.addButton(tr("NO"), QMessageBox::NoRole);
        msgBox.exec();
        if (msgBox.clickedButton()==no) {
            return;
        }
    }
    QString path = QFileDialog::getSaveFileName(
        this,
        "Crea un nuovo allenamento",
        "./IlTuoAllenamento.csv",
        "File CSV *.csv"
    );
    if (path.isEmpty()) {
        return;
    }
    csv=GestoreCSV(path);
    csv.creaFileAllenamento();
    allenamento=Allenamento();
    has_unsaved_changes = false;
    WidgetPrincipale* widgetPrincipale=new WidgetPrincipale(allenamento, this);
    QWidget* oldCentralWidget = takeCentralWidget();
    if(oldCentralWidget) {delete oldCentralWidget;}
    setCentralWidget(widgetPrincipale);
    mostraStato("Nuovo allenamento creato con successo!");
}

void MainWindow::apriAllenamento() {
    if (has_unsaved_changes) {
        QMessageBox msgBox; 
        msgBox.setWindowTitle(tr("Sei sicuro di non voler salvare l'allenamento corrente?"));
        msgBox.setText(tr("Ci sono delle modifiche non salvate, se aprirai un allenamento già esistente queste andranno perse. Sei sicuro di voler continuare?")); 
        msgBox.addButton(tr("SI"), QMessageBox::YesRole); 
        QAbstractButton* no = msgBox.addButton(tr("NO"), QMessageBox::NoRole);
        msgBox.exec();
        if (msgBox.clickedButton()==no) {
            return;
        }
    }
    QString path = QFileDialog::getOpenFileName(
        this,
        "Carica un allenamento già esistente",
        "./",
        "File csv *.csv"
    );
    if (path.isEmpty()) {
        return;
    }
    csv=GestoreCSV(path);
    has_unsaved_changes = false;
    try{
        allenamento=csv.leggiFileAllenamento();
        WidgetPrincipale* widgetPrincipale=new WidgetPrincipale(allenamento, this);
        QWidget* oldCentralWidget = takeCentralWidget();
        if(oldCentralWidget) {delete oldCentralWidget;}
        setCentralWidget(widgetPrincipale);
        mostraStato("Allenamento già esistente caricato con successo!");
    } catch(const std::logic_error& ex){
        creaLabelIniziale();
        QMessageBox::critical(this, "Errore", ex.what());
        mostraStato("Impossibile caricare l'allenamento selezionato :(");
    } catch(...){
        creaLabelIniziale();
        QMessageBox::critical(this, "Errore non identificato", "È avvenuto un errore non previsto durante il caricamento dell'allenamento selezionato");
        mostraStato("Impossibile caricare l'allenamento selezionato :(");
    }
}

void MainWindow::salvaAllenamento() {
    if (csv.isUndefined()) {
        return;
    }
    if(!has_unsaved_changes){ //se non ci sono state modifiche evito la riscittura del file
        mostraStato("Allenamento salvato con successo!");
        return;
    }
    csv.aggiornaFileAllenamento(allenamento);
    has_unsaved_changes = false;
    mostraStato("Allenamento salvato con successo!");
}

void MainWindow::salvaAllenamentoConNome() {
    if (csv.isUndefined()) {
        return;
    }
    QString path = QFileDialog::getSaveFileName(
        this,
        "Crea un nuovo allenamento",
        "./IlTuoAllenamento.csv",
        "File CSV *.csv"
    );
    if (path.isEmpty()) {
        return;
    }
    csv=GestoreCSV(path);
    csv.aggiornaFileAllenamento(allenamento);
    has_unsaved_changes = false;
    mostraStato("Allenamento salvato come \"" + path.split("/").last() + "\" con successo!");
}

void MainWindow::toggleToolbar() {
    toolbar->setVisible(!toolbar->isVisible());
    if(toolbar->isVisible()){
        mostraStato("Barra degli strumenti visibile");
    } else {
        mostraStato("Barra degli strumenti nascosta");
    }
}

void MainWindow::mostraStato(QString messaggio) {
    statusBar()->showMessage(messaggio);
}

void MainWindow::chiudi() {
    if (has_unsaved_changes) {
        QMessageBox msgBox; 
        msgBox.setWindowTitle(tr("Sei sicuro di voler chiudere l'applicazione?"));
        msgBox.setText(tr("Ci sono delle modifiche non salvate, se chiuderai l'applicazione queste andranno perse. Sei sicuro di voler continuare?")); 
        QAbstractButton* si = msgBox.addButton(tr("SI"), QMessageBox::YesRole); 
        msgBox.addButton(tr("NO"), QMessageBox::NoRole);
        msgBox.exec();
        if (msgBox.clickedButton()==si) {
            QApplication::quit();
        }
    }
    else {
        QApplication::quit();
    }
}

}
