#ifndef FILTROTAG_H
#define FILTROTAG_H
#include<QString>
#include"abstractfilter.h"
namespace modello{ namespace filtro
{
class FiltroTag: public AbstractFilter
{
private:
    QString tagTarget;
public:
    FiltroTag(const QString& tagTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTROTAG_H
