#include "EsercizioSerieRipetizioni.h"

EsercizioSerieRipetizioni::EsercizioSerieRipetizioni(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati, unsigned int num_s, unsigned int rec, unsigned int num_r, unsigned int cal): 
Esercizio(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati), 
EsercizioSerie(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati, num_s, rec),
EsercizioRipetizioni(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati, num_r, cal){}

EsercizioSerieRipetizioni* EsercizioSerieRipetizioni::clone() const { return new EsercizioSerieRipetizioni( *this ); }

unsigned int EsercizioSerieRipetizioni::calorieBruciate() const{
    return EsercizioRipetizioni::calorieBruciate()*getNum_serie();
}

std::string EsercizioSerieRipetizioni::tipologiaEsecuzione() const{
    return std::to_string(getNum_serie())+" X "+std::to_string(EsercizioRipetizioni::getNum_ripetizioni());
}

std::string EsercizioSerieRipetizioni::to_CSV() const{
  std::string tipo="EsercizioSerieRipetizioni";
  std::string EsercizioRipetizioni_csv_string = EsercizioRipetizioni::to_CSV();
  return tipo+";"+EsercizioRipetizioni_csv_string.substr(EsercizioRipetizioni_csv_string.find(';')+1)+";"+EsercizioSerie::to_CSV();
}

void EsercizioSerieRipetizioni::accept(EsercizioVisitorInterface& visitor, bool readonly) {
    visitor.visitEsercizioSerieRipetizioni(*this,readonly);
}