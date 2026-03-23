#ifndef LIBRETTO_H
#define LIBRETTO_H
#include"attivita.h"
#include"esame.h"
#include<QString>
namespace modello
{
class Libretto
{
private:
    unsigned int cfu_totali;
    const std::vector<Attivita*>& attivita;
public:
    Libretto(unsigned int cfu_totali,const std::vector<Attivita*>& attivita);
    unsigned int getCfuCompletati() const;
    unsigned int getCfuMancanti() const;
    double getMediaPesata() const;
    double getVotoFinaleAtteso() const;
    std::vector<const Esame*> getEsamiSuperati() const;
    std::vector<const Esame*> getEsamiNonSuperati() const;
    std::vector<const Esame*> getEsamiFuturi() const;
};
}
#endif // LIBRETTO_H
