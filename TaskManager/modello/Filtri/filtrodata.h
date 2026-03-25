#ifndef FILTRODATA_H
#define FILTRODATA_H
#include"abstractfilter.h"
#include<QDate>
namespace modello
{namespace filtro
{
class FiltroData: public AbstractFilter
{
private:
    QDate target;
public:
    FiltroData(const QDate& target);
    bool filtra(const Attivita* a) const override;

};
}}
#endif // FILTRODATA_H
