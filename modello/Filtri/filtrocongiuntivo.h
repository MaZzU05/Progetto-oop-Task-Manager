#ifndef FILTROCONGIUNTIVO_H
#define FILTROCONGIUNTIVO_H
#include"abstractfilter.h"
#include<vector>
namespace modello
{namespace filtro
{
//la gui quando inserirà filtri in questo filtro li allocherà dinamicamente, così li distruggo qua evitando memory leak
class FiltroCongiuntivo:public AbstractFilter
{
private:
    std::vector<AbstractFilter*> filtri;
public:
    FiltroCongiuntivo()=default;
    ~FiltroCongiuntivo();
    void addFiltro(AbstractFilter* f);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROCONGIUNTIVO_H
