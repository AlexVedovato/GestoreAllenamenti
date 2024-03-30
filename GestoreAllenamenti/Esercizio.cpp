#include "Esercizio.h"

Esercizio::Esercizio(const std::string& nom, const std::string& descr, bool card, unsigned int num_gruppi_musc_allenati,
const GruppoMuscolare* gruppi_musc_allenati): nome(nom), descrizione(descr), cardio(card), 
num_gruppi_musc_all(num_gruppi_musc_allenati){
  gruppi_musc_all=new GruppoMuscolare[num_gruppi_musc_allenati];
  for(unsigned int i=0;i<num_gruppi_musc_allenati;i++){
    gruppi_musc_all[i]=gruppi_musc_allenati[i];
  }
}

Esercizio::Esercizio(const Esercizio& es): nome(es.nome), descrizione(es.descrizione), cardio(es.cardio), 
num_gruppi_musc_all(es.num_gruppi_musc_all){
  gruppi_musc_all=new GruppoMuscolare[es.num_gruppi_musc_all];
  for(unsigned int i=0;i<es.num_gruppi_musc_all;i++){
    gruppi_musc_all[i]=es.gruppi_musc_all[i];
  }
}

Esercizio& Esercizio::operator=(const Esercizio& es) {
    if(this != &es) {
      if(gruppi_musc_all!= nullptr) delete[] gruppi_musc_all;
      nome=es.nome;
      descrizione=es.descrizione;
      cardio=es.cardio;
      num_gruppi_musc_all=es.num_gruppi_musc_all;
      gruppi_musc_all=new GruppoMuscolare[es.num_gruppi_musc_all];
      for(unsigned int i=0;i<es.num_gruppi_musc_all;i++){
        gruppi_musc_all[i]=es.gruppi_musc_all[i];
      }
    }
    return *this;
  }

Esercizio::~Esercizio(){
  if(gruppi_musc_all!= nullptr) delete[] gruppi_musc_all;
}

std::string Esercizio::getNome() const{
  return nome;
}

std::string Esercizio::getDescrizione() const{
  return descrizione;
}

bool Esercizio::isCardio() const{
  return cardio;
}

unsigned int Esercizio::getNum_gruppi_musc_all() const{
  return num_gruppi_musc_all;
}

void Esercizio::setNome(const std::string& nom){
  nome=nom;
}

void Esercizio::setDescrizione(const std::string& descr){
  descrizione=descr;
}

bool Esercizio::isGruppoMuscolareAll(const GruppoMuscolare& gm) const{
  for(unsigned int i=0;i<num_gruppi_musc_all;i++){
    if(gruppi_musc_all[i]==gm){
      return true;
    }
  }
  return false;
}

std::string Esercizio::to_CSV() const{
  std::string csv_string=nome+";"+descrizione+";"+std::to_string(cardio)+";"+std::to_string(num_gruppi_musc_all);
  for(unsigned int i=0;i<num_gruppi_musc_all;i++){
    csv_string+=";"+std::to_string(gruppi_musc_all[i]);
  }
  return csv_string;
}