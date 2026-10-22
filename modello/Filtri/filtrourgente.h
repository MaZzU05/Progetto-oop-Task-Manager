#ifndef FILTROURGENTE_H
#define FILTROURGENTE_H

#include "abstractfilter.h"
namespace modello{
namespace filtro
{
class FiltroUrgente : public AbstractFilter
{
private:
    bool isUrgente;
public:
    FiltroUrgente(bool isUrgente);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROURGENTE_H
