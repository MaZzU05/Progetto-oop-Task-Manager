#include "filtroanno.h"
namespace modello
{
namespace filtro

{
FiltroAnno::FiltroAnno(int annoTarget): annoTarget(annoTarget) {}
bool FiltroAnno::filtra(const Attivita* a) const
{
    return annoTarget==a->getDate().date().year();
}

}}
