#include "EsercizioTempo.h"

EsercizioTempo::EsercizioTempo(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati, unsigned int dur, unsigned int cal): 
Esercizio(nom, descr, card, num_gruppi_musc_allenati, gruppi_musc_allenati), durata(dur), calorie_min(cal) {}
    
EsercizioTempo* EsercizioTempo::clone() const { return new EsercizioTempo( *this ); }

unsigned int EsercizioTempo::getDurata() const{
    return durata;
}

void EsercizioTempo::setDurata(unsigned int sec, unsigned int min, unsigned int ore){
    durata=ore*3600+min*60+sec;
}

unsigned int EsercizioTempo::calorieBruciate() const{
    return (static_cast<float>(durata)/60)*calorie_min;
}

std::string EsercizioTempo::tipologiaEsecuzione() const{
    std::string s="";
    unsigned int temp=durata;
    if(temp/3600>0){
        s+=std::to_string(temp/3600)+"h ";
        temp-=(temp/3600)*3600;
    }
    if(temp/60>0 ||(temp%60!=0 && temp<durata)){
        s+=std::to_string(temp/60)+"m ";
        temp-=(temp/60)*60;
    }
    return temp==0? s:s+=std::to_string(temp)+"s";
}

std::string EsercizioTempo::to_CSV() const{
  std::string tipo="EsercizioTempo";
  return tipo+";"+Esercizio::to_CSV()+";"+std::to_string(durata)+";"+std::to_string(calorie_min);
}

void EsercizioTempo::accept(EsercizioVisitorInterface& visitor, bool readonly) {
    visitor.visitEsercizioTempo(*this,readonly);
}