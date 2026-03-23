#include "sport.h"
#include<algorithm>
namespace modello
{
Sport::Sport(const QString& title,
             const unsigned int id,
             const QString& note,
             const QDateTime& dataFine,
             const QString& luogo,
             const QTime& durata,
             bool complete,
             Priority priorita): Attivita(title, id, note, dataFine, complete, priorita), luogo(luogo), durata(durata) {}
Sport* Sport::clone() const
{
    return new Sport(*this);
}
const QString& Sport::getLuogo() const
{
    return luogo;
}
void Sport::setLuogo(const QString& l)
{
    luogo=l;
}
const QTime& Sport::getDurata() const
{
    return durata;
}
void Sport::setDurata(const QTime& d)
{
    durata=d;
}
void Sport::removeGiornoSettimana(Qt::DayOfWeek giornoDaRimuovere)
{
    //remove_if sposta gli elementi validi dopo il past_the_end, e ne ritorna l'iteratore, lo combino con erase
    giorni_sport.erase(std::remove_if(giorni_sport.begin(), giorni_sport.end(), [giornoDaRimuovere](Qt::DayOfWeek d){return d==giornoDaRimuovere;}),giorni_sport.end());
}
void Sport::setGiornoSettimana(Qt::DayOfWeek d)
{
    //auto it=std::find(giorni_sport.begin(), giorni_sport.end(), d);
    //if(it==giorni_sport.end()) giorni_sport.push_back(d);
    if(!isGiornoAllenamento(d)) giorni_sport.push_back(d);

}
bool Sport::isGiornoAllenamento(Qt::DayOfWeek d) const
{
    auto it=std::find(giorni_sport.begin(), giorni_sport.end(), d);
    return it!=giorni_sport.end();
}
//Assumo che l'ora di allenamento sia quella della data di fine, con la seguente regola: Fino al giorno di fine ci si allena nei giorni del vettore alla ora della deta di fine
//non ritorno riferimento perche' devo restituire variabile locale
const QTime Sport::getOraAllenamento() const
{
    return getDate().time();
}
void Sport::accept(ActivityVisitorInterface* visitor)
{
    visitor->visit(this);
}
void Sport::accept(ConstActivityVisitorInterface* visitor) const
{
    visitor->visit(this);
}
//non guardo piu' la data finale, ma se oggi e' uno dei giorni della settimana ove pratico sport
bool Sport::isUrgente() const
{
    if(isComplete()) return false;
    QDate data_oggi=QDate::currentDate();
    QTime ora_attuale=QTime::currentTime();
    Priority prior=getPriority();
    Qt::DayOfWeek giornoSet=static_cast<Qt::DayOfWeek>(data_oggi.dayOfWeek()); //dayOfWeek ritorna un intero, per assegnarlo al tipo DayOfWeek devo castarlo
    double oreMancanti = ora_attuale.secsTo(getOraAllenamento()) / 3600.0;
    if((data_oggi.daysTo(getDate().date())<0)||(isGiornoAllenamento(giornoSet)&&
         (oreMancanti>=0&&
         ((prior==Priority::alta&&(oreMancanti<12))||
         (prior==Priority::media&&(oreMancanti<4))||
                                                                                                             (prior==Priority::bassa&&(oreMancanti<1))))
            ))
        return true;
    return false;
}
}
