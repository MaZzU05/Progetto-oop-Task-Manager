#include "filtronome.h"

namespace modello{
namespace filtro{
FiltroNome::FiltroNome(const QString& nomeTarget): nomeTarget(nomeTarget) {}
bool FiltroNome::filtra(const Attivita* a) const
{
    //metto tutto in minuscolo per ricerca case-insensitive, non cerco corrispondenza esatta, ma che sia sottostringa
    return a->getTitle().toLower().contains(nomeTarget.toLower());
}
}}
