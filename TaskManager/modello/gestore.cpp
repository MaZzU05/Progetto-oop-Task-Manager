#include "gestore.h"
#include <QtCore/qjsonarray.h>
#include<algorithm>
#include"jsonsavervisitor.h"
#include<QJsonDocument>
#include<QFile>
#include<QTextStream>
#include"esame.h"
#include"scadenza.h"
#include"appuntamento.h"
#include"sport.h"
namespace modello
{
Gestore::~Gestore()
{
    for(auto it=listaAttivita.begin(); it!=listaAttivita.end(); it++)
    {
        delete *it;
    }
}
Gestore::Gestore(const Gestore& g)
{
    for( Attivita* a:g.listaAttivita)
    {
        listaAttivita.push_back(a->clone());
    }
}
Gestore& Gestore::operator=(const Gestore& g)
{
    if(this!=&g)
    {
        for(Attivita* a:listaAttivita) delete a;
        listaAttivita.clear();
        for(const Attivita* a:g.listaAttivita) listaAttivita.push_back(a->clone());
    }
    return *this;
}
unsigned int Gestore::generaNuovoId() const
{
    unsigned int max=0;
    if(listaAttivita.size()==0) return 1;
    for(Attivita* a:listaAttivita) if(a->getID()>max) max=a->getID();
    return max+1;

}
void Gestore::addAttivita(Attivita* a)
{
    auto it=std::find(listaAttivita.begin(), listaAttivita.end(), a);
    if(it==listaAttivita.end()) listaAttivita.push_back(a);
}
//***** OCIO: ritorna true se trova l'attivita' e la rimuove, false se non presente (anche se la gui dovrebbe sapere gia' gli id presenti, ricorda di togliere il bool eventualmente)
bool Gestore::removeAttivita(unsigned int id)
{
    //unsigned int check=listaAttivita.size();
    //listaAttivita.erase(std::remove_if(listaAttivita.begin(), listaAttivita.end(), [id](Attivita* a){return a->getID()==id;}),listaAttivita.end()); non dealloca la memoria mannaggia a
    //return check==listaAttivita.size();
    auto it=listaAttivita.begin();
    for(; it!=listaAttivita.end()&&(*it)->getID()!=id; it++);
    if(it!=listaAttivita.end())
    {
        delete *it;
        listaAttivita.erase(it);
        return true;
    }
    return false;

}
//per svuotare dopo salvataggio su json
void Gestore::svuota()
{
    for(Attivita* a:listaAttivita) delete a;
    listaAttivita.clear();
}
const std::vector<Attivita*>& Gestore::getAllAttivita() const
{
    return listaAttivita;
}
//do per assunto che l'id passato sia dentro la lista
Attivita* Gestore::getAttivitaById(unsigned int id) const
{
    for(Attivita* a:listaAttivita) if(a->getID()==id) return a;
    return nullptr;
}
std::vector<Attivita*> Gestore::filtra(const filtro::AbstractFilter& af) const
{
    std::vector<Attivita*> aux;
    std::for_each(listaAttivita.begin(), listaAttivita.end(),
                  [&af, &aux](Attivita* a)
                  {
        if(af.filtra(a)) aux.push_back(a);
    });
    return aux;
}
 bool Gestore::salva(const QString& nomeFile) const
{
     QJsonArray daSalvare;
    JsonSaverVisitor visitor;
     for(Attivita* a:listaAttivita)
     {
         a->accept(&visitor);
         daSalvare.append(visitor.getJsonObject());
     }
     QJsonDocument doc; //"contenitore" dove appoggio il QJsonArray, necessario prima del salvataggio
     doc.setArray(daSalvare);
     //va trasformato in sequenza di byte, uso indented che occupa piu' spazio ma e' piu' leggibile, almeno per essere sicuro funzioni correttamente
     QByteArray datiJson=doc.toJson(QJsonDocument::Indented);
     //apro il file
     QFile file(nomeFile);
     //controllo se l'apertura funziona, altrimenti ritorno falso
     if(file.open(QIODevice::WriteOnly))
     {
         file.write(datiJson);
         file.close();
         return true;
     }
     return false;
}
bool Gestore::carica(const QString& nomeFile)
{
    //seguiro il processo inverso al salvataggio
    //svuoto le attivita' attualmente in ram, se no avrei duplicati
    svuota();
    QFile file(nomeFile);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray datiJson=file.readAll();
        QJsonDocument doc=QJsonDocument::fromJson(datiJson);
        QJsonArray daCaricare=doc.array();
        for (auto it=daCaricare.begin(); it!=daCaricare.end(); it++)
        {
            QJsonObject aux=(*it).toObject();
            QString tipo=aux["Tipo"].toString();
            if(tipo!="Esame"&&tipo!="Scadenza"&&tipo!="Appuntamento"&&tipo!="Sport")
            {
                svuota();
                file.close();
                return false;
            }
            //gli attributi della base li estrago gia', per rispettare il principio DRY
            //so che alcuni cast sono impliciti ma li esplicito per leggibilita'
            QString title=aux["title"].toString();
            unsigned int id=static_cast<unsigned int>(aux["id"].toInt());
            QString note=aux["note"].toString();
            bool complete=aux["complete"].toBool();
            //leggo dalla stringa in formato iso, converte automaticamente in data
            QDateTime dataCreazione=QDateTime::fromString(aux["dataCreazione"].toString(), Qt::ISODate);
            QDateTime dataFine=QDateTime::fromString(aux["dataFine"].toString(), Qt::ISODate);
            unsigned int durata=static_cast<unsigned int>(aux["durata"].toInt());
            Priority priorita=static_cast<Priority>(aux["priorita"].toInt());
            if(tipo=="Esame")
            {

                unsigned int cfu=static_cast<unsigned int>(aux["cfu"].toInt());
                unsigned int voto=static_cast<unsigned int>(aux["voto"].toInt());
                bool lode=aux["lode"].toBool();
                QString sede=aux["sede"].toString();
                Esame* e=new Esame(title, id, note, sede, cfu, dataFine, durata, complete, priorita);
                e->changeDataCreazione(dataCreazione);
                e->setVoto(voto);
                e->modifyLode(lode);
                QJsonArray tempTag=aux["tag"].toArray();
                for(auto it=tempTag.begin(); it!=tempTag.end(); it++)
                {
                    e->addTag(it->toString());
                }
                QJsonArray tempProf=aux["professori"].toArray();
                for(auto it=tempProf.begin(); it!=tempProf.end(); it++)
                {
                    e->addProfessor(it->toString());
                }
                addAttivita(e);

            }
            else if(tipo=="Scadenza")
            {
                unsigned int giorniPreavviso=static_cast<unsigned int>(aux["giorniPreavviso"].toInt());
                Scadenza* s=new Scadenza(title, id, note, dataFine, giorniPreavviso, durata, complete, priorita);
                s->changeDataCreazione(dataCreazione);
                QJsonArray tempTag=aux["tag"].toArray();
                for(auto it=tempTag.begin(); it!=tempTag.end(); it++)
                {
                    s->addTag(it->toString());
                }
                QJsonArray tempToDo=aux["todoList"].toArray();
                for(auto it=tempToDo.begin(); it!=tempToDo.end(); it++)
                {
                    QJsonObject sottoTask=it->toObject();
                    s->addPassaggio(sottoTask["descrizione"].toString());
                    s->setPassaggioCompletato(sottoTask["descrizione"].toString(), sottoTask["completa"].toBool());
                }
                addAttivita(s);

            }
            else if(tipo=="Appuntamento")
            {
                QString luogo=aux["luogo"].toString();
                bool inPresenza=aux["inPresenza"].toBool();
                Appuntamento* a=new Appuntamento(title, id, note, dataFine, luogo, durata,inPresenza, complete, priorita);
                a->changeDataCreazione(dataCreazione);
                QJsonArray tempTag=aux["tag"].toArray();
                for(auto it=tempTag.begin(); it!=tempTag.end(); it++)
                {
                    a->addTag(it->toString());
                }
                QJsonArray tempPartecipanti=aux["partecipanti"].toArray();
                for(auto it=tempPartecipanti.begin(); it!=tempPartecipanti.end(); it++)
                {
                    a->addPartecipante(it->toString());
                }
                addAttivita(a);

            }
            else if(tipo=="Sport")
            {
                QString luogo=aux["luogo"].toString();
                QDate dataInizio=QDate::fromString(aux["dataInizio"].toString(),Qt::ISODate);
                Sport* s=new Sport(title, id, note, dataFine, durata,dataInizio,luogo, complete, priorita);
                s->changeDataCreazione(dataCreazione);
                QJsonArray tempTag=aux["tag"].toArray();
                for(auto it=tempTag.begin(); it!=tempTag.end(); it++)
                {
                    s->addTag(it->toString());
                }
                QJsonArray tempGiorniSport=aux["giorni_sport"].toArray();
                for(auto it=tempGiorniSport.begin(); it!=tempGiorniSport.end(); it++)
                {
                    s->setGiornoSettimana(static_cast<Qt::DayOfWeek>(it->toInt()));
                }
                addAttivita(s);
            }

        }
        file.close();
        return true;
    }
    return false;

}
}
