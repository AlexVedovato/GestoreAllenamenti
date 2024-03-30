#ifndef ESERCIZIO_H
#define ESERCIZIO_H

#include <string>
#include "EsercizioVisitorInterface.h"

enum GruppoMuscolare{petto=1, dorso=2, bicipiti=3, tricipiti=4, spalle=5, quadricipiti=6, polpacci=7, glutei=8, addominali=9};

class Esercizio {
  private:
    std::string nome;
    std::string descrizione;
    bool cardio;
    unsigned int num_gruppi_musc_all;
    GruppoMuscolare* gruppi_musc_all;

  public:
    Esercizio(const std::string&, const std::string&, bool, unsigned int, const GruppoMuscolare*);
    Esercizio(const Esercizio&);
    Esercizio& operator=(const Esercizio&);
    virtual ~Esercizio();
    virtual Esercizio* clone() const = 0; 

    std::string getNome() const;
    std::string getDescrizione() const;
    bool isCardio() const;
    unsigned int getNum_gruppi_musc_all() const;

    void setNome(const std::string&);
    void setDescrizione(const std::string&);

    bool isGruppoMuscolareAll(const GruppoMuscolare&) const; //metodo per capire se un determinato gruppo muscolare è allenato o meno da un esercizio

    virtual unsigned int calorieBruciate() const = 0;
    virtual std::string tipologiaEsecuzione() const = 0; 

    virtual std::string to_CSV() const; 

    virtual void accept(EsercizioVisitorInterface&, bool) = 0;
};


#endif
