#include "AggiungiDialog.h"

namespace View {

AggiungiDialog::AggiungiDialog(Esercizio*& es, unsigned int& p, QDialog* parent): QDialog(parent), esercizio(es),
posizione(p) {

  setWindowTitle("Aggiungi un esercizio all'allenamento");
  resize(600, 600); 
  
  QVBoxLayout* vbox = new QVBoxLayout(this);
  vbox->setAlignment(Qt::AlignCenter);
  QLabel* label = new QLabel("Scegli l'esercizio che vuoi aggiungere al tuo allenamento:");
  vbox->addWidget(label);
  QListWidget* listWidget = new QListWidget;
  GestoreCSV csv(":CSV/ListaEsercizi.csv");
  try{
    lista_esercizi=csv.leggiFileAllenamento();
    for(auto cit=lista_esercizi.begin();cit!=lista_esercizi.end();++cit){
      QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(cit->getNome()));
      item->setTextAlignment(Qt::AlignCenter);
      listWidget->addItem(item);
    }
  }catch(...){
    QMessageBox::critical(this, "Errore", "È avvenuto un errore durante il caricamento della lista di esercizi. Probabilemente è stato modificato o cancellato il file \"ListaEsercizi.csv\", fondamentale per il corretto funzionamento dell'applicazione. Se così fosse si è pregati di riscaricare suddetto file e di inserirlo all'interno della cartella \"CSV\".");
    reject();
  }
  vbox->addWidget(listWidget);
  QGroupBox* groupBox = new QGroupBox("Filtra la ricerca:");
  QRadioButton* radio1 = new QRadioButton("Per tipo di esercizio");
  radio1->setChecked(true);
  QRadioButton* radio2 = new QRadioButton("Per gruppo muscolare allenato");
  QComboBox* comboBox = new QComboBox;
  comboBox->addItem("EsercizioRipetizioni",QVariant(1));
  comboBox->addItem("EsercizioTempo",QVariant(2));
  comboBox->addItem("EsercizioSerie",QVariant(3));
  comboBox->addItem("EsercizioSerieRipetizioni",QVariant(4));
  comboBox->addItem("EsercizioSerieTempo",QVariant(5));
  QPushButton* apply = new QPushButton("Applica filtro");
  QPushButton* reset = new QPushButton("Annulla filtro applicato");
  reset->setEnabled(false);
  QGridLayout* grid = new QGridLayout;
  grid->addWidget(radio1,0,0);
  grid->addWidget(radio2,0,1);
  grid->addWidget(comboBox,1,0);
  grid->addWidget(apply,1,1);
  grid->addWidget(reset,2,0,1,2);
  groupBox->setLayout(grid);
  vbox->addWidget(groupBox);
  QFrame* line=new QFrame;
  line->setFrameStyle(QFrame::HLine);
  line->setLineWidth(10);  
  line->setMidLineWidth(20);
  vbox->addWidget(line);
  esercizio=lista_esercizi[0].clone();
  listWidget->setCurrentRow(0);
  widgetEsercizio=new WidgetEsercizio(esercizio,false);
  QHBoxLayout* hbox_esercizio = new QHBoxLayout;
  hbox_esercizio->setAlignment(Qt::AlignCenter);
  hbox_esercizio->addWidget(widgetEsercizio);
  vbox->addLayout(hbox_esercizio);
  QHBoxLayout* hbox_posizione = new QHBoxLayout;
  hbox_posizione->setAlignment(Qt::AlignCenter);
  QLabel* label_posizione = new QLabel("In che posizione vuoi aggiungere l'esercizio: ");
  input_posizione = new QLineEdit(QString::number(posizione+1));
  input_posizione->setValidator(new QIntValidator(1, posizione+1));
  hbox_posizione->addWidget(label_posizione);
  hbox_posizione->addWidget(input_posizione);
  vbox->addLayout(hbox_posizione);
  QHBoxLayout* hbox = new QHBoxLayout;
  hbox->setAlignment(Qt::AlignCenter);
  QPushButton* annulla = new QPushButton("Annulla");
  QPushButton* aggiungi = new QPushButton("Aggiungi esercizio");
  hbox->addWidget(annulla);
  hbox->addWidget(aggiungi);
  vbox->addLayout(hbox);

  connect(annulla, &QPushButton::clicked, this, &QDialog::reject);
  connect(aggiungi, &QPushButton::clicked, this, &AggiungiDialog::gestisciInput);

  /*
  I seguenti segnali vengono collegati a delle lambda-espressioni; questo per evitare di dover definire slot privati e di 
  dover salvare come membri della classe i vari puntatori ai diversi widget utilizzati.
  Difatti, vista la difficile riusabilità di questo codice per casi esterni al loro utilizzo principale e/o vista la
  relativa semplicità delle espressioni, questo rende la gestione del codice più semplice, intuitiva e veloce.
  */

  connect(radio1, &QRadioButton::toggled, [comboBox](bool checked) {
    if (checked){
      comboBox->clear();
      comboBox->addItem("EsercizioRipetizioni",QVariant(1));
      comboBox->addItem("EsercizioTempo",QVariant(2));
      comboBox->addItem("EsercizioSerie",QVariant(3));
      comboBox->addItem("EsercizioSerieRipetizioni",QVariant(4));
      comboBox->addItem("EsercizioSerieTempo",QVariant(5));
    }
  });
  
  connect(radio2, &QRadioButton::toggled, [comboBox](bool checked) {
    if (checked){
      comboBox->clear();
      comboBox->addItem("Petto",QVariant(GruppoMuscolare::petto));
      comboBox->addItem("Dorso",QVariant(GruppoMuscolare::dorso));
      comboBox->addItem("Bicipiti",QVariant(GruppoMuscolare::bicipiti));
      comboBox->addItem("Tricipiti",QVariant(GruppoMuscolare::tricipiti));
      comboBox->addItem("Spalle",QVariant(GruppoMuscolare::spalle));
      comboBox->addItem("Quadricipiti",QVariant(GruppoMuscolare::quadricipiti));
      comboBox->addItem("Polpacci",QVariant(GruppoMuscolare::polpacci));
      comboBox->addItem("Glutei",QVariant(GruppoMuscolare::glutei));
      comboBox->addItem("Addominali",QVariant(GruppoMuscolare::addominali));
    }
  });

  connect(apply, &QPushButton::clicked, [radio1,radio2,comboBox,apply,reset,listWidget,this]() {
    if(radio1->isChecked() || radio2->isChecked()){
      listWidget->clear();
      if(radio1->isChecked()){
        int tipo=comboBox->currentData().toInt();
        Allenamento esercizi_tipo;
        if(tipo==1){
          esercizi_tipo=lista_esercizi.eserciziClasse<EsercizioRipetizioni>();
        } else if(tipo==2){
          esercizi_tipo=lista_esercizi.eserciziClasse<EsercizioTempo>();
        } else if(tipo==3){
          esercizi_tipo=lista_esercizi.eserciziClasse<EsercizioSerie>();
        } else if(tipo==4){
          esercizi_tipo=lista_esercizi.eserciziClasse<EsercizioSerieRipetizioni>();
        } else {
          esercizi_tipo=lista_esercizi.eserciziClasse<EsercizioSerieTempo>();
        }
        for(auto cit=esercizi_tipo.begin();cit!=esercizi_tipo.end();++cit){
          QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(cit->getNome()));
          item->setTextAlignment(Qt::AlignCenter);
          listWidget->addItem(item);
        }
      } else { //radio2.isChecked()
        Allenamento esercizi_gm=lista_esercizi.eserciziGruppoMuscolare(comboBox->currentData().value<GruppoMuscolare>());
        for(auto cit=esercizi_gm.begin();cit!=esercizi_gm.end();++cit){
          QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(cit->getNome()));
          item->setTextAlignment(Qt::AlignCenter);
          listWidget->addItem(item);
        }
      }
      radio1->setEnabled(false);
      radio2->setEnabled(false);
      comboBox->setEnabled(false);
      apply->setEnabled(false);
      reset->setEnabled(true);
    }
  });

  connect(reset, &QPushButton::clicked, [radio1,radio2,comboBox,apply,reset,listWidget,this]() {
    listWidget->clear();
    for(auto cit=lista_esercizi.begin();cit!=lista_esercizi.end();++cit){
      QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(cit->getNome()));
      item->setTextAlignment(Qt::AlignCenter);
      listWidget->addItem(item);
    }
    radio1->setEnabled(true);
    radio2->setEnabled(true);
    comboBox->setEnabled(true);
    apply->setEnabled(true);
    reset->setEnabled(false);
  });

  connect(input_posizione, &QLineEdit::textChanged, [this]() {
  	  if(!input_posizione->text().isEmpty()){
        unsigned int input = input_posizione->text().toUInt();
        if (input > posizione+1) {
          input_posizione->setText(QString::number(posizione+1));
        }
        if (input < 1) {
          input_posizione->setText(QString::number(1));
        }
      }
	});

  connect(listWidget, &QListWidget::currentItemChanged, this, [listWidget,hbox_esercizio,this](QListWidgetItem *current) {
    if(current){
      QString nome = current->text();
      delete esercizio;
      esercizio=lista_esercizi.esercizioNome(nome.toStdString()).clone();
      delete widgetEsercizio;
      widgetEsercizio=new WidgetEsercizio(esercizio,false);
      hbox_esercizio->addWidget(widgetEsercizio);
    }
  });
}

void AggiungiDialog::gestisciInput(){
  try{
    widgetEsercizio->gestisciInput();
  } catch(std::string ex){
    QMessageBox::warning(this, "Errore", QString::fromStdString(ex), QMessageBox::Ok);
    return;
  }
  if(input_posizione->text().isEmpty()){
    QMessageBox::warning(this, "Errore", "Posizione dell'esercizio all'interno dell'allenamento mancante", QMessageBox::Ok);
    return;
  }
  posizione=input_posizione->text().toUInt()-1;
  accept();
}

}