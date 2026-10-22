#include "jsonsavervisitor.h"
#include<QJsonArray>
#include<QString>
#include<QDateTime>
#include<QDate>
#include<vector>
#include"esame.h"
#include"scadenza.h"
#include"appuntamento.h"
#include"sport.h"
#include<utility>

namespace modello
{
//scritta per evitare di riscrivere il codice 4 volte, rispettando il principio DRY
void JsonSaverVisitor::preparaBase(const Attivita* a)
{
    //svuoto preventivamente
    daSalvare = QJsonObject();
    //attributi della base
    daSalvare["title"]=a->getTitle();
    //devo convertirlo da unsigned int a int o double per salvarlo nel QJsonObject, so che ci sarebbe il rischio di overflow ma e' ragionevole pensare di non avere cosi tante attivita
    daSalvare["id"]=static_cast<int>(a->getID());
    daSalvare["note"]=a->getNote();
    daSalvare["complete"]=a->isComplete();
    //Per contenitori interni prima li devo salvare in un QJsonArray e poi salvare l'array nell'object
    QJsonArray tag;
    std::vector<QString> vecTag=a->getAllTag();
    for( const QString& t:vecTag) tag.append(t);
    daSalvare["tag"]=tag;
    //essendo un tipo particolare di Qt, lo converto a tipo primitivo con toString e come parametro ISODate che e' standard per le date e utile per la conversione interna
    daSalvare["dataCreazione"]=a->getDataCreazione().toString(Qt::ISODate);
    daSalvare["dataFine"]=a->getDate().toString(Qt::ISODate);
    daSalvare["durata"]=static_cast<int>(a->getDurata());
    //per il tipo enumerativo lo casto a int e quando carichero' faro l'operazione inversa
    daSalvare["priorita"]=static_cast<int>(a->getPriority());

}

void JsonSaverVisitor::visit(const Esame* e)
{
    preparaBase(e);
    daSalvare["Tipo"]="Esame";
    daSalvare["cfu"]=static_cast<int>(e->getCFU());
    daSalvare["voto"]=static_cast<int>(e->getVoto());
    daSalvare["lode"]=e->hasLode();
    daSalvare["sede"]=e->getSede();
    QJsonArray professori;
    std::vector<QString> vecProf=e->getAllProf();
    for(const QString& p:vecProf) professori.append(p);
    daSalvare["professori"]=professori;
}

void JsonSaverVisitor::visit(const Scadenza* s)
{
    preparaBase(s);
    daSalvare["Tipo"]="Scadenza";
    daSalvare["giorniPreavviso"]=static_cast<int>(s->getGiorniPreavviso());
    //per toDoList che e' una classe interna privata faccio una gestione ad hoc(anche per il salvataggio), creo dei QJsonObject, e li salvo nel QJsonArray
    QJsonArray todoList;
    std::vector<std::pair<QString,bool>> vecToDo=s->getAllSottoTask();
    for(const std::pair<QString, bool>& temp:vecToDo)
    {
        QJsonObject aux;
        aux["descrizione"]=temp.first;
        aux["completa"]=temp.second;
        todoList.append(aux);
    }
    daSalvare["todoList"]=todoList;

}

void JsonSaverVisitor::visit(const Appuntamento* a)
{
    preparaBase(a);
    daSalvare["Tipo"]="Appuntamento";
    daSalvare["luogo"]=a->getLuogo();
    daSalvare["inPresenza"]=a->isInPresenza();
    QJsonArray partecipanti;
    std::vector<QString> vecPartecipanti=a->getAllPartecipanti();
    for(const QString& p:vecPartecipanti) partecipanti.append(p);
    daSalvare["partecipanti"]=partecipanti;

}

void JsonSaverVisitor::visit(const Sport* s)
{
    preparaBase(s);
    daSalvare["Tipo"]="Sport";
    daSalvare["luogo"]=s->getLuogo();
    daSalvare["dataInizio"]=s->getDataInizio().toString(Qt::ISODate);
    QJsonArray giorni_sport;
    std::vector<Qt::DayOfWeek> vecGiorniSport=s->getAllGiorniSettimanali();
    for(const Qt::DayOfWeek& d:vecGiorniSport) giorni_sport.append(static_cast<int>(d));
    daSalvare["giorni_sport"]=giorni_sport;
}
QJsonObject JsonSaverVisitor::getJsonObject() const
{
    return daSalvare;
}
}
