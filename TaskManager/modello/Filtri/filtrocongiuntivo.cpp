#include "filtrocongiuntivo.h"
namespace modello
{namespace filtro
{

FiltroCongiuntivo::~FiltroCongiuntivo()
{
    for(AbstractFilter* a:filtri) delete a;
    filtri.clear();
}
void FiltroCongiuntivo::addFiltro(AbstractFilter* f)
{
    filtri.push_back(f);
}
bool FiltroCongiuntivo::filtra(const Attivita* a) const
{
    for(AbstractFilter* af:filtri) if(!(af->filtra(a))) return false;
    return true;
}
}}
