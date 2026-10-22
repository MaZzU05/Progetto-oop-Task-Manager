#include "filtrotag.h"

namespace modello
{
namespace filtro
{
FiltroTag::FiltroTag(const QString& tagTarget):tagTarget(tagTarget) {}
bool FiltroTag::filtra(const Attivita* a) const
{
    return a->tagIsIn(tagTarget);
}
}
}
