#ifndef ESERCIZIOSERIE_H
#define ESERCIZIOSERIE_H

#include "Esercizio.h"

class EsercizioSerie: virtual public Esercizio {
  private:
    unsigned int num_serie; //>=2 (altrimenti chiaramente non è un esercizio composto da più serie)
    unsigned int recupero; //tempo di recupero tra una serie e l'altra in secondi 

  public:
    EsercizioSerie(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*, unsigned int, unsigned int);
    
    unsigned int getNum_serie() const;
    unsigned int getRecupero() const;
    std::string getStringRecupero() const;

    void setNum_serie(unsigned int);
    void setRecupero(unsigned int, unsigned int=0);

    std::string to_CSV() const override; 
};


#endif