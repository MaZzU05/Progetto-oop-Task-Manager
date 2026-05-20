#ifndef FILTROANNO_H
#define FILTROANNO_H
#include"abstractfilter.h"
//il metodo year dei QDate restituiscono un intero, mi è sufficiente passare quindi un int valido in input
namespace modello{
namespace filtro
{
class FiltroAnno: public AbstractFilter
{
private:
     int annoTarget;
public:
    FiltroAnno(int annoTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROANNO_H
