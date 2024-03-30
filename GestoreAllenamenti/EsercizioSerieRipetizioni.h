#ifndef ESERCIZIOSERIERIPETIZIONI_H
#define ESERCIZIOSERIERIPETIZIONI_H

#include "EsercizioSerie.h"
#include "EsercizioRipetizioni.h"

class EsercizioSerieRipetizioni: public EsercizioSerie, public EsercizioRipetizioni {

  public:
    EsercizioSerieRipetizioni(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*, unsigned int, unsigned int, unsigned int, unsigned int);
    EsercizioSerieRipetizioni* clone() const override; 

    unsigned int calorieBruciate() const override;
    std::string tipologiaEsecuzione() const override;

    std::string to_CSV() const override; 

    void accept(EsercizioVisitorInterface&, bool) override;
};


#endif