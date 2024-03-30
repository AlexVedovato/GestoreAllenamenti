#ifndef ESERCIZIORIPETIZIONI_H
#define ESERCIZIORIPETIZIONI_H

#include "Esercizio.h"

class EsercizioRipetizioni: virtual public Esercizio {
  private:
    unsigned int num_ripetizioni;
    unsigned int calorie_rep; //numero di calorie bruciate per una singola ripetizione

  public:
    EsercizioRipetizioni(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*, unsigned int, unsigned int);
    EsercizioRipetizioni* clone() const override; 
    
    unsigned int getNum_ripetizioni() const;

    void setNum_ripetizioni(unsigned int);

    unsigned int calorieBruciate() const override;
    std::string tipologiaEsecuzione() const override;

    std::string to_CSV() const override; 

    void accept(EsercizioVisitorInterface&, bool) override;
};


#endif