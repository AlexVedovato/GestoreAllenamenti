#include "MostraDialog.h"

namespace View {

MostraDialog::MostraDialog(Esercizio* es, QDialog* parent): QDialog(parent){

  setWindowTitle("Dettagli dell' esercizio");
  resize(400, 400); 
  
  QVBoxLayout* vbox = new QVBoxLayout(this);
  vbox->setAlignment(Qt::AlignCenter);
  WidgetEsercizio* widgetEsercizio=new WidgetEsercizio(es,true);
  QHBoxLayout* hbox_esercizio = new QHBoxLayout;
  hbox_esercizio->setAlignment(Qt::AlignCenter);
  hbox_esercizio->addWidget(widgetEsercizio);
  vbox->addLayout(hbox_esercizio);
}

}