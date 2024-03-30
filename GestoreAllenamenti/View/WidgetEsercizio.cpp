#include "WidgetEsercizio.h"

namespace View {

WidgetEsercizio::WidgetEsercizio(Esercizio*& es, bool ro, QWidget* parent): QWidget(parent), 
esercizio(es), readonly(ro) {

    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setAlignment(Qt::AlignCenter);
    setLayout(vbox);

    QHBoxLayout* hbox_nome = new QHBoxLayout;
    hbox_nome->setAlignment(Qt::AlignCenter);
    QLabel* label_nome = new QLabel("Nome:");
    nome = new QTextEdit();
    nome->setLineWrapMode(QTextEdit::NoWrap);
    QSize size = nome->document()->size().toSize();
    nome->setFixedHeight(size.height()+3);
    nome->setReadOnly(readonly);
    nome->setText(QString::fromStdString(esercizio->getNome()));
    hbox_nome->addWidget(label_nome);
    hbox_nome->addWidget(nome);
    vbox->addLayout(hbox_nome);

    QHBoxLayout* hbox_descrizione = new QHBoxLayout;
    hbox_descrizione->setAlignment(Qt::AlignCenter);
    QLabel* label_descrizione = new QLabel("Descrizione:");
    descrizione = new QTextEdit();
    descrizione->setLineWrapMode(QTextEdit::WidgetWidth);
    descrizione->setReadOnly(readonly);
    descrizione->setText(QString::fromStdString(esercizio->getDescrizione()));
    hbox_descrizione->addWidget(label_descrizione);
    hbox_descrizione->addWidget(descrizione);
    vbox->addLayout(hbox_descrizione);

    QLabel* cardio = new QLabel(esercizio->isCardio()?"Questo esercizio è considerato cardio.":"Questo esercizio non è considerato cardio.");
    vbox->addWidget(cardio);

    QPixmap base(":assets/base.jpeg");
    QPixmap immagine_finale(base.size());
    QPainter painter(&immagine_finale);
    painter.drawPixmap(0, 0, base);
    /*
    per disegnare i vari gruppi muscolari allenati avrei potuto utilizzare un ciclo for, ciclando su valori interi, tuttavia 
    per questione di leggibilità ho preferito fare un if per ogni gruppo muscolare, anche perchè non prevedo grandi modifiche
    sull'enum in questione, dato che i gruppi muscolari non dovrebbero cambiare nel tempo.
    */
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::petto)){
        QPixmap petto(":assets/petto.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, petto);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::dorso)){
        QPixmap dorso(":assets/dorso.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, dorso);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::bicipiti)){
        QPixmap bicipiti(":assets/bicipiti.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, bicipiti);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::tricipiti)){
        QPixmap tricipiti(":assets/tricipiti.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, tricipiti);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::spalle)){
        QPixmap spalle(":assets/spalle.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, spalle);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::quadricipiti)){
        QPixmap quadricipiti(":assets/quadricipiti.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, quadricipiti);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::polpacci)){
        QPixmap polpacci(":assets/polpacci.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, polpacci);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::glutei)){
        QPixmap glutei(":assets/glutei.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, glutei);
    }
    if(esercizio->isGruppoMuscolareAll(GruppoMuscolare::addominali)){
        QPixmap addominali(":assets/addominali.png");
        painter.translate(0, 0);
        painter.drawPixmap(0, 0, addominali);
    }
    painter.end();
    QGridLayout* grid = new QGridLayout;
    QLabel* muscoli_allenati = new QLabel();
    muscoli_allenati->setPixmap(immagine_finale.scaledToHeight(150));
    muscoli_allenati->setAlignment(Qt::AlignCenter);
    grid->addWidget(muscoli_allenati,0,0);
    esercizio->accept(visitor,readonly);
    grid->addWidget(visitor.getWidget(),0,1);
    vbox->addLayout(grid);
    if(readonly){
        QLabel* label_calorie = new QLabel("Numero di calore bruciate dall'esercizio: "+QString::number(esercizio->calorieBruciate()));
        vbox->addWidget(label_calorie);
    }

    /*
    I seguenti segnali vengono collegati a delle lambda-espressioni; questo per evitare di dover definire slot privati solo 
    per una semplice gestione dell'input dell'utente. 
    Difatti, vista la relativa semplicità delle espressioni, questo rende la gestione più semplice, intuitiva e veloce.
    */
    connect(nome, &QTextEdit::textChanged, [this]() {
	    QString text = nome->toPlainText();
	    //impedisce l'inserimento di più di 15 caratteri per il nome dell'esercizio
	    if (text.length() > 30) {
		QTextCursor cursor = nome->textCursor();
		cursor.movePosition(QTextCursor::End);
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
		cursor.deleteChar();
	    }
	    //impedisce l'inserimento del carattere ';' all'interno del nome dell'esercizio per evitare problemi col salvataggio in CSV
	    if (text.contains(";")) {
		QTextCursor cursor = nome->textCursor();
		cursor.setPosition(text.indexOf(";"), QTextCursor::MoveAnchor);
		cursor.deleteChar();
	    }
	});
	
	connect(descrizione, &QTextEdit::textChanged, [this]() {
	    QString text = descrizione->toPlainText();
	    //impedisce l'inserimento di più di 400 caratteri per la descrizione dell'esercizio
	    if (text.length() > 400) {
		QTextCursor cursor = descrizione->textCursor();
		cursor.movePosition(QTextCursor::End);
		cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
		cursor.deleteChar();
	    }
	    //impedisce l'inserimento del carattere ';' all'interno della descrizione dell'esercizio per evitare problemi col salvataggio in CSV
	    if (text.contains(";")) {
		QTextCursor cursor = descrizione->textCursor();
		cursor.setPosition(text.indexOf(";"), QTextCursor::MoveAnchor);
		cursor.deleteChar();
	    }
	});
}

void WidgetEsercizio::gestisciInput(){
  visitor.gestisciInput();
  if(nome->toPlainText().isEmpty()){
    throw std::string("Nome mancante");
  }
  if(descrizione->toPlainText().isEmpty()){
    throw std::string("Descrizione mancante");
  }
  esercizio->setNome(nome->toPlainText().replace('\n',' ').toStdString());
  esercizio->setDescrizione(descrizione->toPlainText().replace('\n',' ').toStdString());
}

}