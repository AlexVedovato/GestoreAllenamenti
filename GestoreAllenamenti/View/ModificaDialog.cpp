#include "ModificaDialog.h"

namespace View {

ModificaDialog::ModificaDialog(Esercizio*& es, QDialog* parent): QDialog(parent), esercizio(es){

  setWindowTitle("Modifica l'esercizio");
  resize(400, 400); 
  
  QVBoxLayout* vbox = new QVBoxLayout(this);
  vbox->setAlignment(Qt::AlignCenter);
  widgetEsercizio=new WidgetEsercizio(esercizio,false);
  QHBoxLayout* hbox_esercizio = new QHBoxLayout;
  hbox_esercizio->setAlignment(Qt::AlignCenter);
  hbox_esercizio->addWidget(widgetEsercizio);
  vbox->addLayout(hbox_esercizio);
  QHBoxLayout* hbox = new QHBoxLayout;
  hbox->setAlignment(Qt::AlignCenter);
  QPushButton* annulla = new QPushButton("Annulla");
  QPushButton* modifica = new QPushButton("Applica le modifiche");
  hbox->addWidget(annulla);
  hbox->addWidget(modifica);
  vbox->addLayout(hbox);

  connect(annulla, &QPushButton::clicked, this, &QDialog::reject);
  connect(modifica, &QPushButton::clicked, this, &ModificaDialog::gestisciInput);
}

void ModificaDialog::gestisciInput(){
  try{
    widgetEsercizio->gestisciInput();
  } catch(std::string ex){
    QMessageBox::warning(this, "Errore", QString::fromStdString(ex), QMessageBox::Ok);
    return;
  }
  accept();
}

}