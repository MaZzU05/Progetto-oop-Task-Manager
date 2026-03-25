#include "filtrodata.h"
namespace modello
{namespace filtro
{
FiltroData::FiltroData(const QDate& target): target(target) {}
bool FiltroData::filtra(const Attivita* a) const
{
    return a->getDate().date()==target;
}

}}
