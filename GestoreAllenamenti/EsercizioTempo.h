#ifndef ESERCIZIOTEMPO_H
#define ESERCIZIOTEMPO_H

#include "Esercizio.h"

class EsercizioTempo: virtual public Esercizio {
  private:
    unsigned int durata; //durata in secondi dell'esercizio
    unsigned int calorie_min; //numero di calorie bruciate per minuto

  public:
    EsercizioTempo(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*, unsigned int, unsigned int);
    EsercizioTempo* clone() const override; 
    
    unsigned int getDurata() const;

    void setDurata(unsigned int, unsigned int=0, unsigned int=0);

    unsigned int calorieBruciate() const override;
    std::string tipologiaEsecuzione() const override;

    std::string to_CSV() const override; 

    void accept(EsercizioVisitorInterface&, bool) override;
};


#endif