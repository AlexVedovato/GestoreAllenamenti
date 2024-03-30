#ifndef GESTORECSV_H
#define GESTORECSV_H

#include <QTextStream>
#include <QFile>
#include <QStringList>
#include"EsercizioSerieTempo.h"
#include"EsercizioSerieRipetizioni.h"
#include"Allenamento.h"

class GestoreCSV {
  private:
    QString path;

  public:
    GestoreCSV(const QString& ="");

    bool isUndefined() const;
    void creaFileAllenamento() const;
    void aggiornaFileAllenamento(const Allenamento&) const;
    Allenamento leggiFileAllenamento();
};


#endif
