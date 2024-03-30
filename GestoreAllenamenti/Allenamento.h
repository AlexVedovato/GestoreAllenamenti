#ifndef ALLENAMENTO_H
#define ALLENAMENTO_H

#include "Esercizio.h"
#include <stdexcept>

class Allenamento { //contenitore di esercizi polimorfi sul modello di Vector adattato alle mie necessità
private:
  Esercizio** a;
  unsigned int num_es; //equivalente di size
  unsigned int capacity;
public:
  Allenamento();
  Allenamento(const Allenamento&);
  Allenamento& operator=(const Allenamento&);
  ~Allenamento();

  Esercizio& operator[](unsigned int); //metodo per la lettura/scrittura di un esercizio dell'allenamento data la sua posizione
  const Esercizio& operator[](unsigned int) const; //metodo per la sola lettura di un esercizio dell'allenamento data la sua posizione

  bool empty() const;
  unsigned int getNum_es() const;
  void push_back(const Esercizio&); //metodo per l'inserimento in coda di un esercizio
  void insert(const Esercizio&, unsigned int); //metodo per l'inserimento in una posizione qualsiasi di un esercizio
  Esercizio& get(unsigned int); //metodo per la lettura/scrittura di un esercizio dell'allenamento data la sua posizione
  const Esercizio& get(unsigned int) const; //metodo per la sola lettura di un esercizio dell'allenamento data la sua posizione
  void pop_back(); //metodo per la cancellazione dell'ultimo esercizio dell'allenamento
  void erase(unsigned int); //metodo per la cancellazione di un esercizio dell'allenamento in una posizione qualsiasi
  void replace(unsigned int, const Esercizio&) const; //metodo per la sostituzione di un esercizio in una determinata posizione dell'allenamento con un altro esercizio
  const Esercizio& esercizioNome(std::string) const; //metodo per la ricerca di uno specifico esercizio all'interno dell'allenamento, il quale ha una determinata stringa come nome 
  Allenamento eserciziCardio() const; //metodo per la ricerca di esercizi considerati come cardio all'interno dell'allenamento
  Allenamento eserciziString(std::string) const; //metodo per la ricerca di esercizi all'interno dell'allenamento i quali contengono una determinata stringa all'interno del nome 
  Allenamento eserciziGruppoMuscolare(GruppoMuscolare) const; //metodo per la ricerca di esercizi che allenano un determinato gruppo muscolare all'interno dell'allenamento
  
  template <class T> 
  Allenamento eserciziClasse() const{ //template per la ricerca di esercizi di una certa classe(o derivati) all'interno dell'allenamento
    Allenamento a_c;
    for(const_iterator cit=cbegin();cit!=cend();cit++){
      if(dynamic_cast<const T*>(&(*cit))!=0){
        a_c.push_back(*cit);
      }
    }
    return a_c;
  }

  class const_iterator {
    friend class Allenamento;
  private:
    const Esercizio** ptrPtr;
    const_iterator(const Esercizio**);
  public:
    
    const_iterator();

    const_iterator& operator++();
    
    const_iterator operator++(int);

    const_iterator& operator--();
    
    const_iterator operator--(int);

    const Esercizio& operator*() const;
    
    const Esercizio* operator->() const;

    bool operator==(const const_iterator&) const;
    
    bool operator!=(const const_iterator&) const;
  };

  const_iterator begin() const;

  const_iterator end() const;

  const_iterator cbegin() const;

  const_iterator cend() const;

  class iterator {
    friend class Allenamento;
  private:
    Esercizio** ptrPtr;
    iterator(Esercizio**);
  public:
    
    iterator();

    iterator& operator++();
    
    iterator operator++(int);

    iterator& operator--();
    
    iterator operator--(int);

    Esercizio& operator*() const;
    
    Esercizio* operator->() const;

    bool operator==(const iterator&) const;
    
    bool operator!=(const iterator&) const;
  };
  
  iterator begin();

  iterator end();
};

#endif