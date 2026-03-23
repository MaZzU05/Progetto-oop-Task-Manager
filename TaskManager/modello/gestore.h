#ifndef GESTORE_H
#define GESTORE_H
#include"attivita.h"
#include"abstractfilter.h"
#include<vector>
namespace modello
{
class Gestore
{
private:
    std::vector<Attivita*> listaAttivita;
public:
    Gestore()=default;
    ~Gestore();
    //rule of three
    Gestore(const Gestore&);
    bool operator!=(const Gestore& g) const;
    Gestore& operator=(const Gestore&);
    unsigned int generaNuovoId() const;
    void addAttivita(Attivita* a);
    bool removeAttivita(unsigned int id);
    //per svuotare dopo salvataggio su json
    void svuota();
    const std::vector<Attivita*>& getAllAttivita() const;
    Attivita* getAttivitaById(unsigned int id) const;
    std::vector<Attivita*> filtra(const AbstractFilter& af) const;
};
}
#endif // GESTORE_H
