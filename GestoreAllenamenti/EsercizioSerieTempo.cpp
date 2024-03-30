#include "EsercizioSerieTempo.h"

EsercizioSerieTempo::EsercizioSerieTempo(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati, unsigned int num_s, unsigned int rec, unsigned int dur, unsigned int cal): 
Esercizio(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati), 
EsercizioSerie(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati, num_s, rec),
EsercizioTempo(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati, dur, cal){}

EsercizioSerieTempo* EsercizioSerieTempo::clone() const { return new EsercizioSerieTempo( *this ); }

unsigned int EsercizioSerieTempo::calorieBruciate() const{
    return EsercizioTempo::calorieBruciate()*getNum_serie();
}

std::string EsercizioSerieTempo::tipologiaEsecuzione() const{
    return std::to_string(getNum_serie())+" X "+EsercizioTempo::tipologiaEsecuzione();
}

std::string EsercizioSerieTempo::to_CSV() const{
  std::string tipo="EsercizioSerieTempo";
  std::string EsercizioTempo_csv_string = EsercizioTempo::to_CSV();
  return tipo+";"+EsercizioTempo_csv_string.substr(EsercizioTempo_csv_string.find(';')+1)+";"+EsercizioSerie::to_CSV();
}

void EsercizioSerieTempo::accept(EsercizioVisitorInterface& visitor, bool readonly) {
    visitor.visitEsercizioSerieTempo(*this,readonly);
}