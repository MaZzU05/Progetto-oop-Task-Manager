#include "attivita.h"
#include<algorithm>
namespace modello
{
//per id unico fallo esternamente, univocita' nella lista
Attivita::Attivita(const QString& title,
         const unsigned int id,
         const QString& note,
         bool complete,
                   Priority priorita): title(title), id(id), note(note), complete(complete), dataCreazione(QDateTime::currentDateTime()), priorita(priorita) {}
const QString& Attivita::getTitle() const
{return title;}
void Attivita::setTitle(const QString& tit)
{
    title=tit;
}
unsigned int Attivita::getID() const
{
    return id;
}
const QString& Attivita::getNote() const
{
    return note;
}
void Attivita::setNote(const QString& nota)
{
    note=nota;
}
const std::vector<QString>& Attivita::getAllTag() const
{
    return tag;
}
void Attivita::addTag(const QString& t)
{
    tag.push_back(t);
}
Priority Attivita::getPriority() const
{
    return priorita;
}
void Attivita::changePriority(Priority nuova)
{
    priorita=nuova;
}
bool Attivita::isComplete() const
{
    return complete;
}
void Attivita::setComplete(bool flag)
{
    complete=flag;
}
const QDateTime& Attivita::getDataCreazione() const
{
    return dataCreazione;
}
bool Attivita::tagIsIn(const QString& t) const
{
    /* con find fa piu' figo
    bool sentinella=false;
    for(auto it=tag.begin(); it!=tag.end()&&!sentinella; it++) sentinella=(t==*it);
    return sentinella;
*/
    return std::find(tag.begin(), tag.end(), t)!=tag.end();
}
}
