#include "EsercizioSerie.h"

EsercizioSerie::EsercizioSerie(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati, unsigned int num_s, unsigned int rec): 
Esercizio(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati), 
num_serie(num_s<2? 2 : num_s), recupero(rec){}

unsigned int EsercizioSerie::getNum_serie() const{
    return num_serie;
}

unsigned int EsercizioSerie::getRecupero() const{
    return recupero;
}

std::string EsercizioSerie::getStringRecupero() const{
    std::string s="";
    unsigned int temp=recupero;
    if(temp/60>0){
        s+=std::to_string(temp/60)+"m ";
        temp-=(temp/60)*60;
    }
    return temp==0? s:s+=std::to_string(temp)+"s";
}

void EsercizioSerie::setNum_serie(unsigned int num_s){
    num_s<2? num_serie=2 : num_serie=num_s;
}

void EsercizioSerie::setRecupero(unsigned int sec, unsigned int min){
    recupero=min*60+sec;
}

std::string EsercizioSerie::to_CSV() const{
  return std::to_string(num_serie)+";"+std::to_string(recupero);
}