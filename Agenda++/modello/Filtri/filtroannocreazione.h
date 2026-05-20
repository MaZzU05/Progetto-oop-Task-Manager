#ifndef FILTROANNOCREAZIONE_H
#define FILTROANNOCREAZIONE_H
#include"abstractfilter.h"
namespace modello
{namespace filtro
{
class FiltroAnnoCreazione: public AbstractFilter
{
private:
    int annoTarget;
public:
    FiltroAnnoCreazione(int annoTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROANNOCREAZIONE_H
