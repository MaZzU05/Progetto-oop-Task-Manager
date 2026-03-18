#include "scadenza.h"
#include<algorithm>
namespace modello
{
Scadenza::Scadenza(const QString& title,
         const unsigned int id,
         const QString& note,
         const QDateTime& dataFine,
         unsigned int giorniPreavviso,
         bool complete,
                   Priority priorita):Attivita(title, id, note, dataFine, complete, priorita), giorniPreavviso(giorniPreavviso) {}
unsigned int Scadenza::getGiorniPreavviso() const
{return giorniPreavviso;}
void Scadenza::setGiorniPreavviso(unsigned int g)
{
    giorniPreavviso=g;
}
void Scadenza::addPassaggio(const QString& p)
{
    todoList.push_back(p);
}
void Scadenza::setPassaggioCompletato(unsigned int index, bool completato)
{
    todoList.at(index).completa=completato;
}
unsigned int Scadenza::getPassaggiTotali() const
{
    //unsigned int conta=0;
    //for(auto it=todoList.begin(); it!=todoList.end(); it++) conta++;
    return todoList.size();
}
unsigned int Scadenza::getPassaggiCompletati() const
{
    unsigned int conta=0;
    std::for_each(todoList.begin(), todoList.end(), [&conta](const SottoTask& t)->void{if(t.completa) conta++;});
    return conta;
}
void Scadenza::accept(ActivityVisitorInterface* visitor)
{
    visitor->visit(this);
}
void Scadenza::accept(ConstActivityVisitorInterface* visitor) const
{
    visitor->visit(this);
}
bool Scadenza::isUrgente() const
{
    if(isComplete()) return false;
   Priority prior=getPriority();
    if(prior==Priority::alta) return true;
    QDate oggi=QDate::currentDate();
    int giorniMancanti=oggi.daysTo(getDate().date());
    //le date passate saranno urgenti per indicare che l'attività è scaduta senza essere stata indicata come completata
    if((giorniMancanti<0||static_cast<unsigned int>(giorniMancanti)<giorniPreavviso)||(prior==Priority::media&&getPassaggiTotali()-getPassaggiCompletati()>5)||(prior==Priority::bassa&&getPassaggiTotali()-getPassaggiCompletati()>=10))
        return true;
    return false;
}
}
