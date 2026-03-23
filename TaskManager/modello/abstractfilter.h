#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H
#include"attivita.h"
namespace modello
{
class AbstractFilter
{
public:
    virtual ~AbstractFilter()=default;
    virtual bool filtra(const Attivita* a) const=0;
};
}
#endif // ABSTRACTFILTER_H
