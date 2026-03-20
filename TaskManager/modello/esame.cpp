#include "esame.h"
namespace modello
{
Esame::Esame(const QString& title,
      const unsigned int id,
      const QString& note,
      const QString& sede,
      const unsigned int cfu,
      const QDateTime& dataEsame,
      bool complete,
             Priority priorita): Attivita(title,id,note,dataEsame,complete,priorita),cfu(cfu),voto(0), lode(false), sede(sede),  verbalizzabile(false) {}
unsigned int Esame::getCFU() const
{
    return cfu;
}
unsigned int Esame::getVoto() const
{
    return voto;
}
bool Esame::setVoto(unsigned int v)
{
    if(v<=30)
    {voto=v;
     verbalizzabile=(voto>=18);
     setComplete();
     if(voto!=30) lode=false;
    return true;}
    return false;

}
void Esame::changeCfu(unsigned int c)
{
    if (c) cfu=c; //non esiste esame da 0 cfu
}
void Esame::modifyLode(bool l)
{
    if(voto==30) lode=l;
    else lode=false;
}

const QString& Esame::getSede() const
{
    return sede;
}
void Esame::setSede(const QString& nuova)
{
    sede=nuova;
}
bool Esame::hasLode() const
{return lode;}
bool Esame::isPassed() const
{
    return verbalizzabile;
}
bool Esame::isProfessorIn(const QString& prof) const
{
   auto it=std::find(professori.begin(), professori.end(), prof);
    return it!=professori.end();
}
void Esame::addProfessor(const QString& prof)
{
    if(!isProfessorIn(prof)) professori.push_back(prof);
}
//restituisco falso se non era presente
bool Esame::removeProfessor(const QString& Prof)
{
    if(!isProfessorIn(Prof)) return false;
    professori.erase(std::remove_if(professori.begin(), professori.end(), [&Prof](const QString& p){return p==Prof;}), professori.end());
    return true;
}
void Esame::accept(ActivityVisitorInterface* visitor)
{
    visitor->visit(this);
}
void Esame::accept(ConstActivityVisitorInterface* visitor) const
{
    visitor->visit(this);
}
bool Esame::isUrgente() const
{
    if(isComplete()) return false;
    Priority prior=getPriority();
    if(prior==Priority::alta) return true;
    //verifica per giorni, ignorando l'ora per indicare l'urgenza
    QDate oggi=QDate::currentDate();
    int giorniMancanti=oggi.daysTo(getDate().date());

    if((giorniMancanti<0)||(prior==Priority::media&&((cfu>6&&giorniMancanti<=30)||(cfu<=6&&giorniMancanti<=14)))
        ||(prior==Priority::bassa&&((cfu>6&&giorniMancanti<=14)||(cfu<=6&&giorniMancanti<=7))))
    return true;
    return false;
}
}
