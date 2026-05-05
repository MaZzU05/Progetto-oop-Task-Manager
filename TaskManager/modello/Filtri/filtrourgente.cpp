#include "filtrourgente.h"
namespace modello
{namespace filtro
{
FiltroUrgente::FiltroUrgente(bool isUrgente): isUrgente(isUrgente) {}

bool FiltroUrgente::filtra(const Attivita* a) const
{
    return a->isUrgente() == isUrgente;
}

}}
