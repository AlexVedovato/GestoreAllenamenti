#ifndef ESERCIZIO_VISITOR_INTERFACE_H
#define ESERCIZIO_VISITOR_INTERFACE_H

class EsercizioRipetizioni;
class EsercizioTempo;
class EsercizioSerie;
class EsercizioSerieRipetizioni;
class EsercizioSerieTempo;

class EsercizioVisitorInterface {
  public:
    virtual ~EsercizioVisitorInterface() = default;
    virtual void visitEsercizioRipetizioni(EsercizioRipetizioni&, bool) = 0;
    virtual void visitEsercizioTempo(EsercizioTempo&, bool) = 0;
    virtual void visitEsercizioSerie(EsercizioSerie*, bool) = 0;
    virtual void visitEsercizioSerieRipetizioni(EsercizioSerieRipetizioni&, bool) = 0;
    virtual void visitEsercizioSerieTempo(EsercizioSerieTempo&, bool) = 0;
};

#endif