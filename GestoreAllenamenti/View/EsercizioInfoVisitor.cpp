#include "EsercizioInfoVisitor.h"

namespace View {

EsercizioInfoVisitor::EsercizioInfoVisitor(): widget(new QWidget), ripetizioni(nullptr), ore_durata(nullptr), 
minuti_durata(nullptr), secondi_durata(nullptr), serie(nullptr), minuti_recupero(nullptr), secondi_recupero(nullptr){}

QWidget* EsercizioInfoVisitor::getWidget() {
    return widget;
}

void EsercizioInfoVisitor::visitEsercizioRipetizioni(EsercizioRipetizioni& esercizio_rep, bool readonly){
    QVBoxLayout* vbox = qobject_cast<QVBoxLayout*>(widget->layout());
    if(!vbox){
      widget = new QWidget;
      vbox = new QVBoxLayout;
      vbox->setAlignment(Qt::AlignCenter);
      widget->setLayout(vbox);
    }
    QHBoxLayout* hbox = new QHBoxLayout;
    QLabel* label = new QLabel("Numero di ripetizioni:");
    hbox->addWidget(label);
    ripetizioni = new QLineEdit(QString::number(esercizio_rep.getNum_ripetizioni()));
    ripetizioni->setValidator(new QIntValidator(1, 20));
    ripetizioni->setReadOnly(readonly);
    hbox->addWidget(ripetizioni);
    vbox->addLayout(hbox);

    widget->connect(ripetizioni, &QLineEdit::textChanged, [this,&esercizio_rep]() {
  	  if(!ripetizioni->text().isEmpty()){
        unsigned int input = ripetizioni->text().toUInt();
        if (input > 20) {
          ripetizioni->setText(QString::number(20));
          esercizio_rep.setNum_ripetizioni(20);
        } else if (input < 1) {
          ripetizioni->setText(QString::number(1));
          esercizio_rep.setNum_ripetizioni(1);
        } else {
          esercizio_rep.setNum_ripetizioni(input);
        }
      }
	});
}

void EsercizioInfoVisitor::visitEsercizioTempo(EsercizioTempo& esercizio_tempo, bool readonly){
    QVBoxLayout* vbox = qobject_cast<QVBoxLayout*>(widget->layout());
    if(!vbox){
      widget = new QWidget;
      vbox = new QVBoxLayout;
      vbox->setAlignment(Qt::AlignCenter);
      widget->setLayout(vbox);
    }
    QHBoxLayout* hbox = new QHBoxLayout;
    QLabel* label = new QLabel("Durata: ");
    hbox->addWidget(label);
    unsigned int temp=esercizio_tempo.getDurata();
    ore_durata = new QLineEdit(QString::number(temp/3600));
    ore_durata->setValidator(new QIntValidator(0, 3));
    temp-=(temp/3600)*3600;
    minuti_durata = new QLineEdit(QString::number(temp/60));
    minuti_durata->setValidator(new QIntValidator(0,59));
    temp-=(temp/60)*60;
    secondi_durata = new QLineEdit(QString::number(temp));
    secondi_durata->setValidator(new QIntValidator(0,59));
    ore_durata->setReadOnly(readonly);
    minuti_durata->setReadOnly(readonly);
    secondi_durata->setReadOnly(readonly);
    hbox->addWidget(ore_durata);
    hbox->addWidget(new QLabel("h   "));
    hbox->addWidget(minuti_durata);
    hbox->addWidget(new QLabel("m   "));
    hbox->addWidget(secondi_durata);
    hbox->addWidget(new QLabel("s   "));
    vbox->addLayout(hbox);

    widget->connect(ore_durata, &QLineEdit::textChanged, [this,&esercizio_tempo]() {
  	  if(!ore_durata->text().isEmpty()){
        unsigned int input = ore_durata->text().toUInt();
        if (input > 3) {
          ore_durata->setText(QString::number(3));
          esercizio_tempo.setDurata(secondi_durata->text().toUInt(),minuti_durata->text().toUInt(),3);
        } else {
          esercizio_tempo.setDurata(secondi_durata->text().toUInt(),minuti_durata->text().toUInt(),input);
        }
      }
	});

    widget->connect(minuti_durata, &QLineEdit::textChanged, [this,&esercizio_tempo]() {
  	  if(!minuti_durata->text().isEmpty()){
        unsigned int input = minuti_durata->text().toUInt();
        if (input > 59) {
          minuti_durata->setText(QString::number(59));
          esercizio_tempo.setDurata(secondi_durata->text().toUInt(),59,ore_durata->text().toUInt());
        } else {
          esercizio_tempo.setDurata(secondi_durata->text().toUInt(),input,ore_durata->text().toUInt());
        }
      }
	});

    widget->connect(secondi_durata, &QLineEdit::textChanged, [this,&esercizio_tempo]() {
  	  if(!secondi_durata->text().isEmpty()){
        unsigned int input = secondi_durata->text().toUInt();
        if (input > 59) {
          secondi_durata->setText(QString::number(59));
          esercizio_tempo.setDurata(59,minuti_durata->text().toUInt(),ore_durata->text().toUInt());
        } else {
          esercizio_tempo.setDurata(input,minuti_durata->text().toUInt(),ore_durata->text().toUInt());
        }
      }
	});
}

void EsercizioInfoVisitor::visitEsercizioSerie(EsercizioSerie* esercizio_serie, bool readonly){
    QVBoxLayout* vbox = qobject_cast<QVBoxLayout*>(widget->layout());
    if(!vbox){
      widget = new QWidget;
      vbox = new QVBoxLayout;
      vbox->setAlignment(Qt::AlignCenter);
      widget->setLayout(vbox);
    }
    QHBoxLayout* hbox_serie = new QHBoxLayout;
    QLabel* label_serie = new QLabel("Numero di serie:");
    hbox_serie->addWidget(label_serie);
    serie = new QLineEdit(QString::number(esercizio_serie->getNum_serie()));
    serie->setValidator(new QIntValidator(2, 10));
    serie->setReadOnly(readonly);
    hbox_serie->addWidget(serie);
    vbox->addLayout(hbox_serie);

    QHBoxLayout* hbox_recupero = new QHBoxLayout;
    QLabel* label_recupero = new QLabel("Recupero: ");
    hbox_recupero->addWidget(label_recupero);
    unsigned int temp=esercizio_serie->getRecupero();
    minuti_recupero = new QLineEdit(QString::number(temp/60));
    minuti_recupero->setValidator(new QIntValidator(0,59));
    temp-=(temp/60)*60;
    secondi_recupero = new QLineEdit(QString::number(temp));
    secondi_recupero->setValidator(new QIntValidator(0,59));
    minuti_recupero->setReadOnly(readonly);
    secondi_recupero->setReadOnly(readonly);
    hbox_recupero->addWidget(minuti_recupero);
    hbox_recupero->addWidget(new QLabel("m   "));
    hbox_recupero->addWidget(secondi_recupero);
    hbox_recupero->addWidget(new QLabel("s   "));
    vbox->addLayout(hbox_recupero);

    widget->connect(serie, &QLineEdit::textChanged, [this,esercizio_serie]() {
  	  if(!serie->text().isEmpty()){
        unsigned int input = serie->text().toUInt();
        if (input > 10) {
          serie->setText(QString::number(10));
          esercizio_serie->setNum_serie(10);
        } else if (input < 2) {
          serie->setText(QString::number(2));
          esercizio_serie->setNum_serie(2);
        } else {
          esercizio_serie->setNum_serie(input);
        }
      }
	});

    widget->connect(minuti_recupero, &QLineEdit::textChanged, [this,esercizio_serie]() {
  	  if(!minuti_recupero->text().isEmpty()){
        unsigned int input = minuti_recupero->text().toUInt();
        if (input > 59) {
          minuti_recupero->setText(QString::number(59));
          esercizio_serie->setRecupero(secondi_recupero->text().toUInt(),59);
        } else {
          esercizio_serie->setRecupero(secondi_recupero->text().toUInt(),input);
        }
      }
	});

    widget->connect(secondi_recupero, &QLineEdit::textChanged, [this,esercizio_serie]() {
  	  if(!secondi_recupero->text().isEmpty()){
        unsigned int input = secondi_recupero->text().toUInt();
        if (input > 59) {
          secondi_recupero->setText(QString::number(59));
          esercizio_serie->setRecupero(59, minuti_recupero->text().toUInt());
        } else {
          esercizio_serie->setRecupero(input, minuti_recupero->text().toUInt());
        }
      }
	});
}

void EsercizioInfoVisitor::visitEsercizioSerieRipetizioni(EsercizioSerieRipetizioni& esercizio_serie_rep, bool readonly){
    visitEsercizioRipetizioni(esercizio_serie_rep,readonly);
    visitEsercizioSerie(&esercizio_serie_rep,readonly);
}

void EsercizioInfoVisitor::visitEsercizioSerieTempo(EsercizioSerieTempo& esercizio_serie_tempo, bool readonly){
    visitEsercizioTempo(esercizio_serie_tempo,readonly);
    visitEsercizioSerie(&esercizio_serie_tempo,readonly);
}

void EsercizioInfoVisitor::gestisciInput(){
    if(widget){
        if(ripetizioni){
            if(ripetizioni->text().isEmpty()){
                throw std::string("Numero di ripetizioni da eseguire per questo esercizio mancante");
            }
        }
        if(ore_durata){
            if(ore_durata->text().isEmpty()){
                throw std::string("Numero di ore di durata dell'esercizio mancante");
            }
        }
        if(minuti_durata){
            if(minuti_durata->text().isEmpty()){
                throw std::string("Numero di minuti di durata dell'esercizio mancante");
            }
        }
        if(secondi_durata){
            if(secondi_durata->text().isEmpty()){
                throw std::string("Numero di secondi di durata dell'esercizio mancante");
            }
        }
        if(serie){
            if(serie->text().isEmpty()){
                throw std::string("Numero di serie da eseguire per questo esercizio mancante");
            }
        }
        if(minuti_recupero){
            if(minuti_recupero->text().isEmpty()){
                throw std::string("Numero di minuti di recupero tra una serie e l'altra dell'esercizio mancante");
            }
        }
        if(secondi_recupero){
            if(secondi_recupero->text().isEmpty()){
                throw std::string("Numero di secondi di recupero tra una serie e l'altra dell'esercizio mancante");
            }
        }
    }
}

}