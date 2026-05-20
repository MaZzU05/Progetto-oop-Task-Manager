#ifndef FILTROMESEANNO_H
#define FILTROMESEANNO_H
#include"abstractfilter.h"
//il metodo month e year dei QDate restituiscono un intero, mi è sufficiente passare quindi un int valido in input
//per essere sicuro di non passare dati ambigui creo un tipo enumerativo per il mese di target
namespace modello
{
namespace filtro
{
enum class MeseTarget: int
{
    Gennaio=1, Febbraio, Marzo, Aprile, Maggio, Giugno, Luglio, Agosto, Settembre, Ottobre, Novembre, Dicembre
};
class FiltroMeseAnno: public AbstractFilter
{
private:
    MeseTarget target;
    int annoTarget;
public:
    FiltroMeseAnno(MeseTarget target, int annoTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROMESEANNO_H
