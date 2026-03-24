#include "filtronome.h"

namespace modello{
namespace filtro{
FiltroNome::FiltroNome(const QString& nomeTarget): nomeTarget(nomeTarget) {}
bool FiltroNome::filtra(const Attivita* a) const
{
    return a->getTitle().toLower().contains(nomeTarget.toLower());
}
}}
