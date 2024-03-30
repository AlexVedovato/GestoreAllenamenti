#ifndef VIEW_ESERCIZIO_INFO_VISITOR_H
#define VIEW_ESERCIZIO_INFO_VISITOR_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QIntValidator>

#include "../EsercizioVisitorInterface.h"
#include "../EsercizioSerieRipetizioni.h"
#include "../EsercizioSerieTempo.h"

namespace View {

class EsercizioInfoVisitor: public EsercizioVisitorInterface {
  private:
    QWidget* widget;
    QLineEdit* ripetizioni;
    QLineEdit* ore_durata;
    QLineEdit* minuti_durata;
    QLineEdit* secondi_durata;
    QLineEdit* serie;
    QLineEdit* minuti_recupero;
    QLineEdit* secondi_recupero;

  public:
    EsercizioInfoVisitor();
    QWidget* getWidget();
    void visitEsercizioRipetizioni(EsercizioRipetizioni&, bool) override;
    void visitEsercizioTempo(EsercizioTempo&, bool) override;
    void visitEsercizioSerie(EsercizioSerie*, bool) override;
    void visitEsercizioSerieRipetizioni(EsercizioSerieRipetizioni&, bool) override;
    void visitEsercizioSerieTempo(EsercizioSerieTempo&, bool) override;

    void gestisciInput();
};

}

#endif