#ifndef FILTRONOME_H
#define FILTRONOME_H
#include"../attivita.h"
#include"abstractfilter.h"
#include<QString>
namespace modello
{namespace filtro
    {
class FiltroNome:public AbstractFilter
{
private:
   QString nomeTarget;
public:
    FiltroNome(const QString& nomeTarget);
    bool filtra(const Attivita* a) const override;
};
}}
#endif // FILTRONOME_H
