#ifndef FILTROCOMPLETATE_H
#define FILTROCOMPLETATE_H
#include"abstractfilter.h"
namespace modello{ namespace filtro{
class FiltroCompletate: public AbstractFilter
{
private:
    bool target; //true se cerco attivita' completate, false altrimenti
public:
    FiltroCompletate(bool target);
    bool filtra(const Attivita*) const override;
};
}}
#endif // FILTROCOMPLETATE_H
