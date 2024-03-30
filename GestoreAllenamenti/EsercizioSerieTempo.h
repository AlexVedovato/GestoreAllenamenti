#ifndef ESERCIZIOSERIETEMPO_H
#define ESERCIZIOSERIETEMPO_H

#include "EsercizioSerie.h"
#include "EsercizioTempo.h"

class EsercizioSerieTempo: public EsercizioSerie, public EsercizioTempo {

  public:
    EsercizioSerieTempo(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*, unsigned int, unsigned int, unsigned int, unsigned int);
    EsercizioSerieTempo* clone() const override; 

    unsigned int calorieBruciate() const override;
    std::string tipologiaEsecuzione() const override;

    std::string to_CSV() const override; 

    void accept(EsercizioVisitorInterface&, bool) override;
};


#endif