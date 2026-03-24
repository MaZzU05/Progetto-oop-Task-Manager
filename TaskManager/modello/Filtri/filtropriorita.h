#ifndef FILTROPRIORITA_H
#define FILTROPRIORITA_H
#include"abstractfilter.h"
namespace modello{ namespace filtro{


class FiltroPriorita:public AbstractFilter
{
private:
    Priority prioritaTarget;
public:
    FiltroPriorita(Priority prioritaTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROPRIORITA_H
