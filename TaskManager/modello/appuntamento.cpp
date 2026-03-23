#include "appuntamento.h"
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<algorithm>
namespace  modello {
Appuntamento::Appuntamento(const QString& title,
             const unsigned int id,
             const QString& note,
             const QDateTime& dataFine,
             const QString& luogo,
             const QTime& durata,
             bool inPresenza,
             bool complete,
            Priority priorita):
    Attivita(title, id, note, dataFine, complete, priorita), luogo(luogo), durata(durata), inPresenza(inPresenza) {}
Appuntamento* Appuntamento::clone() const
{
    return new Appuntamento(*this);
}
const QString& Appuntamento::getLuogo() const
{
    return luogo;
}
void Appuntamento::setLuogo(const QString& l)
{
    luogo=l;
}
const QTime& Appuntamento::getDurata() const
{
    return durata;
}
void Appuntamento::setDurata(const QTime& d)
{
    durata=d;
}
bool Appuntamento::isInPresenza() const
{
    return inPresenza;
}
void Appuntamento::setPresenza(bool p)
{
    inPresenza=p;
}
//verifica con un espressione regolare se la mail è in un formato valido, non serve che verifico nella gui, lo faccio già qua, o forse meglio farlo dopo
//***togliliere controllo se lo faccio da gui!!!!!***
bool Appuntamento::addPartecipante(const QString& partecipante)
{
    //R" per non avere problemi con caratteri speciali, organizzata in due blocchi, 1 accetta tutti i caratteri normali, poi chiocciola, poi nome dominio
    //seguito da . estensione di almeno due caratteri, \. cerca il punto, {2,} riempito almeno 2 volte, quindi per domini>=2
    //restituisce falso se mail non valida, senza inserirla, vero se valida, se già presente non la inserisce
    QRegularExpression re(R"(^[a-zA-Z0-9.]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,}$)");
    QRegularExpressionMatch match=re.match(partecipante);
    if(match.hasMatch())
    {
        auto it=std::find(partecipanti.begin(), partecipanti.end(), partecipante);
        if(it==partecipanti.end()) partecipanti.push_back(partecipante);
        return true;
    }
    return false;

}
void Appuntamento::removePartecipante(const QString& daRimuovere)
{
    auto it=std::find(partecipanti.begin(), partecipanti.end(), daRimuovere);
    if(it!=partecipanti.end()) partecipanti.erase(it);
}
void Appuntamento::accept(ActivityVisitorInterface* visitor)
{
    visitor->visit(this);
}
void Appuntamento::accept(ConstActivityVisitorInterface* visitor) const
{
    (*visitor).visit(this);
}

bool Appuntamento::isUrgente() const
{
    if(isComplete()) return false;
    //non c'è un metodo in QDateTime per vedere le ore di differenza tra due dataora, però per i secondi si, da li calcolo le ore
    QDateTime oggi=QDateTime::currentDateTime();
    double ore_mancanti=oggi.secsTo(getDate());
    if(ore_mancanti<0) return true;
    ore_mancanti/=3600.0; //converto da secondi a ore
    Priority priorita=getPriority();
    if((priorita==Priority::alta&&ore_mancanti<=24)||
      (priorita==Priority::media&&ore_mancanti<=12)||
        (priorita==Priority::bassa&&ore_mancanti<=4))
        return true;
    return false;
}

}
