#include "filtromeseanno.h"
#include<QDate>
namespace modello
{
namespace  filtro
{
FiltroMeseAnno::FiltroMeseAnno(MeseTarget target, int annoTarget): target(target), annoTarget(annoTarget) {}
bool FiltroMeseAnno::filtra(const Attivita* a) const
{
    QDate dataAttivita=a->getDate().date();
    return (dataAttivita.month()==static_cast<int>(target))&&(dataAttivita.year()==annoTarget);
}
}
}
