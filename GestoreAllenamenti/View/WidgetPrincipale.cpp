#include "WidgetPrincipale.h"

namespace View {

WidgetPrincipale::WidgetPrincipale(Allenamento& all, MainWindow* mainW, QWidget* parent): QWidget(parent), 
allenamento(all), mainWindow(mainW), tableWidget(new QTableWidget(0,4,this)) {

    QVBoxLayout* vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignCenter);

    setLayout(vbox);
    
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setStretchLastSection(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setMinimumWidth(650);
    tableWidget->setMinimumHeight(250);
    vbox->addWidget(tableWidget, Qt::AlignCenter);
    
    
    QPushButton* aggiungi = new QPushButton("Aggiungi esercizio  ");
    aggiungi->setIcon(QIcon(":/assets/icons/new_esercizio.svg"));
    aggiungi->setLayoutDirection(Qt::RightToLeft);
    vbox->addWidget(aggiungi, Qt::AlignCenter);
    modifica = new QPushButton("Modifica esercizio  ");
    modifica->setIcon(QIcon(":/assets/icons/edit.svg"));
    modifica->setLayoutDirection(Qt::RightToLeft);
    vbox->addWidget(modifica, Qt::AlignCenter);
    elimina = new QPushButton("Elimina esercizio  ");
    elimina->setIcon(QIcon(":/assets/icons/delete.svg"));
    elimina->setLayoutDirection(Qt::RightToLeft);
    vbox->addWidget(elimina, Qt::AlignCenter);

    if(!all.empty()){
        unsigned int i=0;
        for(auto cit=all.cbegin();cit!=all.cend();++cit, ++i){
            aggiungiRigaEsercizio(*cit, i);
        }
    } else {
        modifica->setEnabled(false);
        elimina->setEnabled(false);
    }

    //Collega il segnale cellDoubleClicked ad una lambda-espressione che annulla una eventuale selezione di riga
    connect(tableWidget, &QTableWidget::cellDoubleClicked, [this]{tableWidget->clearSelection();});

    connect(aggiungi, &QPushButton::clicked, this, &WidgetPrincipale::aggiungiEsercizio);
    connect(modifica, &QPushButton::clicked, this, &WidgetPrincipale::modificaEsercizio);
    connect(elimina, &QPushButton::clicked, this, &WidgetPrincipale::eliminaEsercizio);

}

void WidgetPrincipale::aggiungiRigaEsercizio(const Esercizio& es,unsigned int riga){
    tableWidget->insertRow(riga);
    QTableWidgetItem* nome = new QTableWidgetItem(QString::fromStdString(es.getNome()));
    tableWidget->setItem(riga, 0, nome);
    QTableWidgetItem* esecuzione = new QTableWidgetItem(QString::fromStdString(es.tipologiaEsecuzione()));
    esecuzione->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(riga, 1, esecuzione);
    const EsercizioSerie* es_serie=dynamic_cast<const EsercizioSerie*>(&es);
    if(es_serie){
    	QTableWidgetItem* recupero = new QTableWidgetItem(QString::fromStdString("Recupero: "+es_serie->getStringRecupero()));
        recupero->setTextAlignment(Qt::AlignCenter);
    	tableWidget->setItem(riga, 2, recupero);
    }
    QPushButton* mostra = new QPushButton("Vedi dettagli  ");
    mostra->setIcon(QIcon(":/assets/icons/search.svg"));
    mostra->setLayoutDirection(Qt::RightToLeft);
    tableWidget->setCellWidget(riga, 3, mostra);
    connect(mostra, &QPushButton::clicked, this, &WidgetPrincipale::mostraEsercizio);
}

void WidgetPrincipale::modificaRigaEsercizio(const Esercizio& es,unsigned int riga){
    QTableWidgetItem* nome = new QTableWidgetItem(QString::fromStdString(es.getNome()));
    tableWidget->setItem(riga, 0, nome);
    QTableWidgetItem* esecuzione = new QTableWidgetItem(QString::fromStdString(es.tipologiaEsecuzione()));
    esecuzione->setTextAlignment(Qt::AlignCenter);
    tableWidget->setItem(riga, 1, esecuzione);
    const EsercizioSerie* es_serie=dynamic_cast<const EsercizioSerie*>(&es);
    if(es_serie){
    	QTableWidgetItem* recupero = new QTableWidgetItem(QString::fromStdString("Recupero: "+es_serie->getStringRecupero()));
        recupero->setTextAlignment(Qt::AlignCenter);
    	tableWidget->setItem(riga, 2, recupero);
    }
}

void WidgetPrincipale::mostraEsercizio(){
    mainWindow->mostraStato("Mostrando i dettagli di un esercizio");
    unsigned int posizione = tableWidget->selectedItems()[0]->row();
    MostraDialog* dialog=new MostraDialog(&(allenamento[posizione]));
    dialog->exec();
    mainWindow->mostraStato("");
}

void WidgetPrincipale::aggiungiEsercizio(){
    mainWindow->mostraStato("Aggiungendo un esercizio");
    Esercizio* es=nullptr;
    unsigned int posizione=allenamento.getNum_es();
    AggiungiDialog* dialog=new AggiungiDialog(es,posizione);
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        if(allenamento.empty()){
            modifica->setEnabled(true);
            elimina->setEnabled(true);
        }
        allenamento.insert(*es,posizione);
        aggiungiRigaEsercizio(*es, posizione);
        mainWindow->changesHappened();
        mainWindow->mostraStato("Esercizio aggiunto con successo!");
    } else {
        mainWindow->mostraStato("");
    }
    if(es){delete es;}
}

void WidgetPrincipale::modificaEsercizio(){
    mainWindow->mostraStato("Modificando un esercizio");
	QList<QTableWidgetItem*> selected_items = tableWidget->selectedItems();
    unsigned int posizione;
    if (selected_items.isEmpty()) {
        posizione = tableWidget->rowCount()-1; //se nessun esercizio è selezionato prendo l'ultimo dell'allenamento
    } else {
        posizione = selected_items[0]->row();
    }
    Esercizio* es=allenamento[posizione].clone();
    ModificaDialog* dialog=new ModificaDialog(es);
    int result = dialog->exec();
    if (result == QDialog::Accepted) {
        allenamento.replace(posizione,*es);
        modificaRigaEsercizio(allenamento[posizione], posizione);
        mainWindow->changesHappened();
        mainWindow->mostraStato("Esercizio modificato con successo!");
    } else {
        mainWindow->mostraStato("");
    }
    if(es){delete es;}
}

void WidgetPrincipale::eliminaEsercizio(){
    QList<QTableWidgetItem*> selected_items = tableWidget->selectedItems();
    QMessageBox msgBox; 
    unsigned int riga;
    if (selected_items.isEmpty()) {
        riga = tableWidget->rowCount()-1; //se nessun esercizio è selezionato prendo l'ultimo dell'allenamento
        msgBox.setWindowTitle(tr("Sei sicuro di voler eliminare l'ultimo esercizio della scheda?"));
    } else {
        riga = selected_items[0]->row();
        msgBox.setWindowTitle(tr("Sei sicuro di voler eliminare l'esercizio selezionato?"));
    }
    msgBox.setText(tr("Una volta eliminato non potrai tornare indietro. Sei sicuro di voler continuare?")); 
    QAbstractButton* si = msgBox.addButton(tr("SI"), QMessageBox::YesRole); 
    msgBox.addButton(tr("NO"), QMessageBox::NoRole);
    msgBox.exec();
    if (msgBox.clickedButton()==si) {
        allenamento.erase(riga);
        tableWidget->removeRow(riga);
        tableWidget->clearSelection();
        mainWindow->changesHappened();
        mainWindow->mostraStato("Esercizio eliminato con successo!");
        if(allenamento.empty()){
            modifica->setEnabled(false);
            elimina->setEnabled(false);
        }
    }
}


}