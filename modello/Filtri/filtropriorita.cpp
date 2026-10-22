#include "filtropriorita.h"

namespace modello{ namespace filtro
{
FiltroPriorita::FiltroPriorita(Priority prioritaTarget): prioritaTarget(prioritaTarget) {}
bool FiltroPriorita::filtra(const Attivita* a) const
{
    return prioritaTarget==a->getPriority();
}

}}
