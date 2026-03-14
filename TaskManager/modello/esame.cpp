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
             Priority priorita): Attivita(title,id,note,complete,priorita),cfu(cfu),voto(0), lode(false), sede(sede), dataEsame(dataEsame), verbalizzabile(false) {}
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
void Esame::changeDate(const QDate& data)
{
    dataEsame.setDate(data);
}
void Esame::changeTime(const QTime& time)
{
    dataEsame.setTime(time);
}
const QDateTime& Esame::getDate() const
{
    return dataEsame;
}
const QString& Esame::getSede() const
{
    return sede;
}
void Esame::setSede(const QString& nuova)
{
    sede=nuova;
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
    int giorniMancanti=oggi.daysTo(dataEsame.date());
    if(prior==Priority::media)
    {
        if(cfu>6&&giorniMancanti<=30) return true;
        if(cfu<=6&&giorniMancanti<=14) return true;
        return false;
    }
    if(cfu>6&&giorniMancanti<=14) return true;
    if(cfu<=6&&giorniMancanti<=7) return true;
    return false;
}
}
