#include "libretto.h"
#include<algorithm>

//utilizzo RTTI per verificare se l'attivita  e' un esame, non ho individuato altri pattern polimorfi utili per evitare cio' in maniera sensata, es un visitor avrebbe solo un campo utile e tutto il resto vuoto e perderebbe il suo senso

namespace modello
{
Libretto::Libretto(unsigned int cfu_totali,const std::vector<Attivita*>& attivita): cfu_totali(cfu_totali), attivita(attivita){}
unsigned int Libretto::getCfuCompletati() const
{
    unsigned int cfu=0;
    std::vector<const Esame*> aux=getEsamiSuperati();
    std::for_each(aux.begin(), aux.end(),
                  [&cfu](const Esame* e)
                  {
                      cfu+=e->getCFU();
                  });
    return cfu;
}
unsigned int Libretto::getCfuMancanti() const
{
    return cfu_totali-getCfuCompletati();
}
double Libretto::getMediaPesata() const
{
    unsigned int cfu=getCfuCompletati();
    if(!cfu) return 0;
    std::vector<const Esame*> aux=getEsamiSuperati();
    double somma_pesata=0;
    std::for_each(aux.begin(), aux.end(),
                  [&somma_pesata](const Esame* e)
                  {
                      somma_pesata+=e->getVoto()*e->getCFU();
    });
    return somma_pesata/cfu;
}
double Libretto::getVotoFinaleAtteso() const
{
    double voto=(getMediaPesata()*110)/30;
    return voto;
}
std::vector<const Esame*> Libretto::getEsamiSuperati() const
{
    std::vector<const Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      const Esame* e=dynamic_cast<const Esame*>(a);
        if(e&&e->isComplete()&&e->isPassed()) aux.push_back(e);
    }
                  );
    return aux;
}
std::vector<const Esame*> Libretto::getEsamiNonSuperati() const
{
    std::vector<const Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      const Esame* e=dynamic_cast<const Esame*>(a);
                      if(e&&e->isComplete()&&!e->isPassed()) aux.push_back(e);
                  }
                  );
    return aux;
}
std::vector<const Esame*> Libretto::getEsamiFuturi() const
{
    std::vector<const Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      const Esame* e=dynamic_cast<const Esame*>(a);
                      if(e&&!e->isComplete()) aux.push_back(e);
                  }
                  );
    return aux;
}
}
