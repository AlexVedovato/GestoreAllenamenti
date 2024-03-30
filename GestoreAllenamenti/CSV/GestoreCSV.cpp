#include "GestoreCSV.h"

GestoreCSV::GestoreCSV(const QString& p):path(p){}

bool GestoreCSV::isUndefined() const{
    return path.isEmpty();
}

void GestoreCSV::creaFileAllenamento() const{
    QFile file(path);
    file.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream stream(&file);
    stream << "tipo di esercizio;nome;descrizione;cardio;numero di gruppi muscolari allenati;gruppi muscolari allenati;campi dati specifici del tipo di esericizio\n";
    file.close();
}

void GestoreCSV::aggiornaFileAllenamento(const Allenamento& allenamento) const{
    QFile file(path);
    file.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream stream(&file);
    stream << "tipo di esercizio;nome;descrizione;cardio;numero di gruppi muscolari allenati;gruppi muscolari allenati;campi dati specifici del tipo di esericizio\n";
    for(auto cit=allenamento.begin();cit!=allenamento.end();++cit){
        stream << QString::fromStdString(cit->to_CSV()) << "\n"; 
    }
    file.close();
}

Allenamento GestoreCSV::leggiFileAllenamento(){
    QFile file(path);
    file.open(QFile::ReadOnly);
    QTextStream stream(&file);
    Allenamento allenamento;
    QString line = stream.readLine();
    int riga=2;
    while (!stream.atEnd()) {
        line = stream.readLine();
        QStringList campi_dati = line.split(';');
        try{
            unsigned int num_gruppi_musc_allenati=std::stoul(campi_dati[4].toStdString());
            if(num_gruppi_musc_allenati<1 || num_gruppi_musc_allenati>9){
                file.close();
                path.clear();
                throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Numero di gruppi muscolari allenati non accettabile");
            }
            GruppoMuscolare gruppi_musc_allenati[num_gruppi_musc_allenati];
            for(unsigned int i=0;i<num_gruppi_musc_allenati;i++){
                GruppoMuscolare gruppo_musc=static_cast<GruppoMuscolare>(std::stoi(campi_dati[5+i].toStdString()));
                if(gruppo_musc<=0 || gruppo_musc>9){
                    file.close();
                    path.clear();
                    throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Gruppo muscolare non riconosciuto");
                }
                gruppi_musc_allenati[i]=gruppo_musc;
            }
            if(campi_dati[0]=="EsercizioRipetizioni"){
                if (campi_dati.size()-num_gruppi_musc_allenati!=7) {path.clear(); file.close(); throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Numero di parametri incorretto");}
                EsercizioRipetizioni es = EsercizioRipetizioni(campi_dati[1].toStdString(), campi_dati[2].toStdString(), campi_dati[3].toStdString()=="1", num_gruppi_musc_allenati, gruppi_musc_allenati, std::stoul(campi_dati[5+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[6+num_gruppi_musc_allenati].toStdString()));
                allenamento.push_back(es);
            } else if(campi_dati[0]=="EsercizioTempo"){
                if (campi_dati.size()-num_gruppi_musc_allenati!=7) {path.clear(); file.close(); throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Numero di parametri incorretto");}
                EsercizioTempo es = EsercizioTempo(campi_dati[1].toStdString(), campi_dati[2].toStdString(), campi_dati[3].toStdString()=="1", num_gruppi_musc_allenati, gruppi_musc_allenati, std::stoul(campi_dati[5+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[6+num_gruppi_musc_allenati].toStdString()));
                allenamento.push_back(es);
            } else if(campi_dati[0]=="EsercizioSerieRipetizioni"){
                if (campi_dati.size()-num_gruppi_musc_allenati!=9) {path.clear(); file.close(); throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Numero di parametri incorretto");}
                EsercizioSerieRipetizioni es = EsercizioSerieRipetizioni(campi_dati[1].toStdString(), campi_dati[2].toStdString(), campi_dati[3].toStdString()=="1", num_gruppi_musc_allenati, gruppi_musc_allenati,  std::stoul(campi_dati[7+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[8+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[5+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[6+num_gruppi_musc_allenati].toStdString()));
                allenamento.push_back(es);
            } else if(campi_dati[0]=="EsercizioSerieTempo"){
                if (campi_dati.size()-num_gruppi_musc_allenati!=9) {path.clear(); file.close(); throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Numero di parametri incorretto");}
                EsercizioSerieTempo es = EsercizioSerieTempo(campi_dati[1].toStdString(), campi_dati[2].toStdString(), campi_dati[3].toStdString()=="1", num_gruppi_musc_allenati, gruppi_musc_allenati, std::stoul(campi_dati[7+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[8+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[5+num_gruppi_musc_allenati].toStdString()), std::stoul(campi_dati[6+num_gruppi_musc_allenati].toStdString()));
                allenamento.push_back(es);
            } else {
                path.clear();
                file.close();
                throw std::logic_error("Errore avvenuto alla riga "+std::to_string(riga)+" -> Tipo di esercizio sconosciuto: "+campi_dati[0].toStdString());
            }
            riga++;
        } catch(const std::invalid_argument& ex){
            path.clear();
            file.close();
            throw std::invalid_argument("Errore avvenuto alla riga "+std::to_string(riga)+" -> Errore dovuto al parsing di qualche dato");
        } catch(...) {
            path.clear();
            file.close();
            throw;
        }
    }
    file.close();
    return allenamento;
}
