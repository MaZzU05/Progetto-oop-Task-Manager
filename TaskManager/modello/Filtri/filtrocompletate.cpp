#include "filtrocompletate.h"

modello::filtro::FiltroCompletate::FiltroCompletate(bool target):target(target) {}
bool modello::filtro::FiltroCompletate::filtra(const Attivita* a) const
{
    return a->isComplete()==target;
}
