#include "scadenza.h"
#include<algorithm>
namespace modello
{
Scadenza::Scadenza(const QString& title,
         const unsigned int id,
         const QString& note,
         const QDateTime& dataFine,
         const unsigned int giorniPreavviso,
         bool complete,
                   Priority priorita):Attivita(title, id, note, dataFine,0, complete, priorita), giorniPreavviso(giorniPreavviso) {}
Scadenza* Scadenza::clone() const
{
    return new Scadenza(*this);
}
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
//La QString passata do per assunto che sia dentro il vettore, la ricevera' dalla gui
void Scadenza::setPassaggioCompletato(const QString& tag_Elemento,  bool completato)
{
    std::for_each(todoList.begin(), todoList.end(), [&tag_Elemento, completato](SottoTask& t){if(t.descrizione==tag_Elemento) t.completa=completato;});
}
unsigned int Scadenza::getNumPassaggiTotali() const
{
    //unsigned int conta=0;
    //for(auto it=todoList.begin(); it!=todoList.end(); it++) conta++;
    return todoList.size();
}
unsigned int Scadenza::getNumPassaggiCompletati() const
{
    unsigned int conta=0;
    std::for_each(todoList.begin(), todoList.end(), [&conta](const SottoTask& t)->void{if(t.completa) conta++;});
    return conta;
}
 std::vector<QString> Scadenza::getPassaggiCompletati() const
{
    std::vector<QString> aux;
    std::for_each(todoList.begin(), todoList.end(), [&aux](const SottoTask& t){if(t.completa) aux.push_back(t.descrizione);});
    return aux;
}
std::vector<QString> Scadenza::getPassaggiNonCompletati() const
{
    std::vector<QString> aux;
    std::for_each(todoList.begin(), todoList.end(), [&aux](const SottoTask& t){if(!t.completa) aux.push_back(t.descrizione);});
    return aux;
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
    if((giorniMancanti<0||static_cast<unsigned int>(giorniMancanti)<giorniPreavviso)||(prior==Priority::media&&getNumPassaggiTotali()-getNumPassaggiCompletati()>5)||(prior==Priority::bassa&&getNumPassaggiTotali()-getNumPassaggiCompletati()>=10))
        return true;
    return false;
}
}
