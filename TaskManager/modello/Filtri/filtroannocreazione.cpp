#include "filtroannocreazione.h"
namespace modello
{
namespace filtro
{
FiltroAnnoCreazione::FiltroAnnoCreazione(int annoTarget): annoTarget(annoTarget) {}
bool FiltroAnnoCreazione::filtra(const Attivita* a) const
{
    return a->getDataCreazione().date().year()==annoTarget;
}
}
}

