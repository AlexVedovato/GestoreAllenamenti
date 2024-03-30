#include "Allenamento.h"

Allenamento::Allenamento():a(new Esercizio*[1]), num_es(0), capacity(1) {}

Allenamento::Allenamento(const Allenamento& b):a(new Esercizio*[b.capacity]), num_es(b.num_es), capacity(b.capacity) {
  for(unsigned int k=0; k<num_es; ++k) {
    a[k]=b.a[k]->clone();
  }
}

Allenamento& Allenamento::operator=(const Allenamento& b) {
  if(this != &b) {
    if(a!= nullptr){
      for(unsigned int k=0; k<num_es; ++k) {
        delete a[k]; 
      }
      delete[] a;
    }
    a=new Esercizio*[b.capacity];
    num_es=b.num_es;
    capacity=b.capacity;
    for(unsigned int k=0; k<num_es; ++k) {
      a[k]=b.a[k]->clone();
    }
  }
  return *this;
}

Allenamento::~Allenamento() {
  if(a!= nullptr){
    for(unsigned int k=0; k<num_es; ++k) {
      delete a[k]; 
    }
    delete[] a;
  }
}

Esercizio& Allenamento::operator[](unsigned int index){
  return *a[index]; 
}

const Esercizio& Allenamento::operator[](unsigned int index) const{
  return *a[index];
}

bool Allenamento::empty() const{
  return num_es==0;
}

unsigned int Allenamento::getNum_es() const {
  return num_es;
}

void Allenamento::push_back(const Esercizio& es){
    insert(es,num_es);
}

void Allenamento::insert(const Esercizio& es, unsigned int index){
    if(index<=num_es){
      if (num_es == capacity) {
        Esercizio** temp = new Esercizio*[2 * capacity];

        for (unsigned int i = 0; i < capacity; i++) {
            temp[i] = a[i];
        }
        
        delete[] a;
        capacity *= 2;
        a = temp;
      }
      for(unsigned int i=num_es;i>index;i--){
        a[i]=a[i-1];
      }
      a[index] = es.clone();
      num_es++;
    }
}

Esercizio& Allenamento::get(unsigned int index){
    return *a[index];
}

const Esercizio& Allenamento::get(unsigned int index) const{
    return *a[index];
}

void Allenamento::pop_back() { 
  erase(num_es-1);
}

void Allenamento::erase(unsigned int index){
    if (index < num_es){
      delete a[index];
      for(unsigned int i=index;i<num_es-1;i++){
        a[i]=a[i+1];
      }
      num_es--;
    }
}

void Allenamento::replace(unsigned int index, const Esercizio& es) const{
  if (index < num_es){
    delete a[index];
    a[index]=es.clone();
  }
}

const Esercizio& Allenamento::esercizioNome(std::string n) const{
  for(const_iterator cit=cbegin();cit!=cend();cit++){
    //se più esercizi hanno lo stesso nome==n ritorna un riferimento costante al primo che trova
    if((*cit).getNome()==n){
      return *cit;
    }
  }
  throw std::out_of_range("Non è stato trovato alcun esercizio con questo nome");
}

Allenamento Allenamento::eserciziCardio() const{
  Allenamento a_cardio;
  for(const_iterator cit=cbegin();cit!=cend();cit++){
    if(cit->isCardio()){
      a_cardio.push_back(*cit);
    }
  }
  return a_cardio;
}

Allenamento Allenamento::eserciziString(std::string s) const{
  Allenamento a_string;
  for(const_iterator cit=cbegin();cit!=cend();cit++){
    if(cit->getNome().find(s) != std::string::npos){
      a_string.push_back(*cit);
    }
  }
  return a_string;
}

Allenamento Allenamento::eserciziGruppoMuscolare(GruppoMuscolare gm) const{
  Allenamento a_gm;
  for(const_iterator cit=cbegin();cit!=cend();cit++){
    if(cit->isGruppoMuscolareAll(gm)){
      a_gm.push_back(*cit);
    }
  }
  return a_gm;
}

Allenamento::const_iterator::const_iterator(const Esercizio** p): ptrPtr(p){}

Allenamento::const_iterator::const_iterator(): ptrPtr(nullptr){}

Allenamento::const_iterator& Allenamento::const_iterator::operator++() {
  ptrPtr++;  
  return *this;
}

Allenamento::const_iterator Allenamento::const_iterator::operator++(int) {
  Allenamento::const_iterator temp=*this;
  ptrPtr++;  
  return temp;
}

Allenamento::const_iterator& Allenamento::const_iterator::operator--() {
  ptrPtr--;  
  return *this;
}

Allenamento::const_iterator Allenamento::const_iterator::operator--(int) {
  Allenamento::const_iterator temp=*this;
  ptrPtr--;  
  return temp;
}

const Esercizio& Allenamento::const_iterator::operator*() const{
  return **ptrPtr;
}

const Esercizio* Allenamento::const_iterator::operator->() const{
  return *ptrPtr;
}

bool Allenamento::const_iterator::operator==(const const_iterator& cit) const {
  return ptrPtr == cit.ptrPtr;
}

bool Allenamento::const_iterator::operator!=(const const_iterator& cit) const {
  return ptrPtr != cit.ptrPtr;
}

Allenamento::const_iterator Allenamento::begin() const {
  if(num_es==0) return const_iterator();
  return Allenamento::const_iterator(const_cast<const Esercizio**>(a));
}

Allenamento::const_iterator Allenamento::end() const {
  if(num_es==0) return const_iterator();
  return Allenamento::const_iterator((const_cast<const Esercizio**>(a))+num_es);
}

Allenamento::const_iterator Allenamento::cbegin() const {
  return begin();
}

Allenamento::const_iterator Allenamento::cend() const {
  return end();
}

Allenamento::iterator::iterator(Esercizio** p): ptrPtr(p){}

Allenamento::iterator::iterator(): ptrPtr(nullptr){}

Allenamento::iterator& Allenamento::iterator::operator++() {
  ptrPtr++;  
  return *this;
}

Allenamento::iterator Allenamento::iterator::operator++(int) {
  Allenamento::iterator temp=*this;
  ptrPtr++;  
  return temp;
}

Allenamento::iterator& Allenamento::iterator::operator--() {
  ptrPtr--;  
  return *this;
}

Allenamento::iterator Allenamento::iterator::operator--(int) {
  Allenamento::iterator temp=*this;
  ptrPtr--;  
  return temp;
}

Esercizio& Allenamento::iterator::operator*() const{
  return **ptrPtr;
}

Esercizio* Allenamento::iterator::operator->() const{
  return *ptrPtr;
}

bool Allenamento::iterator::operator==(const iterator& it) const {
  return ptrPtr == it.ptrPtr;
}

bool Allenamento::iterator::operator!=(const iterator& it) const {
  return ptrPtr != it.ptrPtr;
}

Allenamento::iterator Allenamento::begin() {
  if(num_es==0) return iterator();
  return Allenamento::iterator(a);
}

Allenamento::iterator Allenamento::end() {
  if(num_es==0) return iterator();
  return Allenamento::iterator((a)+num_es);
}