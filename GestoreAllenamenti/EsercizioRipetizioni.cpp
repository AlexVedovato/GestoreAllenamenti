#include "EsercizioRipetizioni.h"

EsercizioRipetizioni::EsercizioRipetizioni(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati, unsigned int num_r, unsigned int cal): 
Esercizio(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati), num_ripetizioni(num_r), calorie_rep(cal) {}
    
EsercizioRipetizioni* EsercizioRipetizioni::clone() const { return new EsercizioRipetizioni( *this ); }

unsigned int EsercizioRipetizioni::getNum_ripetizioni() const{
    return num_ripetizioni;
}

void EsercizioRipetizioni::setNum_ripetizioni(unsigned int num_r){
    num_ripetizioni=num_r;
}

unsigned int EsercizioRipetizioni::calorieBruciate() const{
    return num_ripetizioni*calorie_rep;
}

std::string EsercizioRipetizioni::tipologiaEsecuzione() const{
    return std::to_string(num_ripetizioni)+" reps";
}

std::string EsercizioRipetizioni::to_CSV() const{
  std::string tipo="EsercizioRipetizioni";
  return tipo+";"+Esercizio::to_CSV()+";"+std::to_string(num_ripetizioni)+";"+std::to_string(calorie_rep);
}

void EsercizioRipetizioni::accept(EsercizioVisitorInterface& visitor, bool readonly) {
    visitor.visitEsercizioRipetizioni(*this,readonly);
}