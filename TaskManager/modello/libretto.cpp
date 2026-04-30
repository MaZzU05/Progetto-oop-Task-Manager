#include "libretto.h"
#include<algorithm>

//utilizzo RTTI per verificare se l'attivita  e' un esame, non ho individuato altri pattern polimorfi utili per evitare cio' in maniera sensata, es un visitor avrebbe solo un campo utile e tutto il resto vuoto e perderebbe il suo senso

namespace modello
{
Libretto::Libretto(unsigned int cfu_totali, QString corsoDiLaurea, std::vector<Attivita*>& attivita): cfu_totali(cfu_totali), corsoDiLaurea(corsoDiLaurea),attivita(attivita){}
unsigned int Libretto::getCfuCompletati() const
{
    unsigned int cfu=0;
    std::vector<Esame*> aux=getEsamiSuperati();
    std::for_each(aux.begin(), aux.end(),
                  [&cfu](Esame* e)
                  {
                      cfu+=e->getCFU();
                  });
    return cfu;
}
unsigned int Libretto::getCfuMancanti() const
{
    unsigned int completati = getCfuCompletati();
    return completati >= cfu_totali ? 0 : cfu_totali - completati;

}
double Libretto::getMediaPesata() const
{
    unsigned int cfu=getCfuCompletati();
    if(!cfu) return 0;
    std::vector<Esame*> aux=getEsamiSuperati();
    double somma_pesata=0;
    std::for_each(aux.begin(), aux.end(),
                  [&somma_pesata](Esame* e)
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
std::vector<Esame*> Libretto::getEsamiSuperati() const
{
    std::vector<Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      Esame* e=dynamic_cast<Esame*>(a);
        if(e&&e->isComplete()&&e->isPassed()) aux.push_back(e);
    }
                  );
    return aux;
}
std::vector<Esame*> Libretto::getEsamiNonSuperati() const
{
    std::vector<Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      Esame* e=dynamic_cast<Esame*>(a);
                      if(e&&e->isComplete()&&!e->isPassed()) aux.push_back(e);
                  }
                  );
    return aux;
}
std::vector<Esame*> Libretto::getEsamiFuturi() const
{
    std::vector<Esame*> aux;
    std::for_each(attivita.begin(), attivita.end(),
                  [&aux](Attivita* a)
                  {
                      Esame* e=dynamic_cast<Esame*>(a);
                      if(e&&!e->isComplete()) aux.push_back(e);
                  }
                  );
    return aux;
}
const QString& Libretto::getCorsoLaurea() const
{
    return corsoDiLaurea;
}
void Libretto::setCorsoLaurea(const QString& nuovo)
{
    corsoDiLaurea=nuovo;
}
unsigned int Libretto::getCfu() const
{
    return cfu_totali;
}
void Libretto::setCfu(unsigned int cfu)
{
    cfu_totali=cfu;
}

Libretto& Libretto::operator=(const Libretto& l)
{
    if(this!=&l)
    {
        cfu_totali=l.cfu_totali;
        corsoDiLaurea=l.corsoDiLaurea;
        attivita=l.attivita;
    }
    return *this;
}
Libretto::Libretto(const Libretto& l): cfu_totali(l.cfu_totali), corsoDiLaurea(l.corsoDiLaurea), attivita(l.attivita) {}
}
