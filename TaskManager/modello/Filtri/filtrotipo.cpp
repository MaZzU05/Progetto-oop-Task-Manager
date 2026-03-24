#include "filtrotipo.h"
namespace modello
{
namespace filtro
{
FiltroTipo::FiltroTipo(ricercaTipo tipo_cercato): tipo_cercato(tipo_cercato){}
FiltroTipo::checkVisitor::checkVisitor(FiltroTipo::ricercaTipo tipoTarget): trovato(false), tipoTarget(tipoTarget) {}
void FiltroTipo::checkVisitor::visit(const Esame*)
{
    if(tipoTarget==ricercaTipo::cercaEsame)
        trovato=true;
}
void FiltroTipo::checkVisitor::visit(const Scadenza*)
{
    if(tipoTarget==ricercaTipo::cercaScadenza)
        trovato=true;
}
void FiltroTipo::checkVisitor::visit(const Appuntamento*)
{
    if(tipoTarget==ricercaTipo::cercaAppuntamento)
        trovato=true;
}
void FiltroTipo::checkVisitor::visit(const Sport*)
{
    if(tipoTarget==ricercaTipo::cercaSport)
        trovato=true;
}
bool FiltroTipo::filtra(const Attivita* a) const
{
    checkVisitor visitor(tipo_cercato);
    a->accept(&visitor);
    return visitor.trovato;
}
}
}

