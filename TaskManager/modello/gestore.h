#ifndef GESTORE_H
#define GESTORE_H
#include"attivita.h"
#include"Filtri/abstractfilter.h"
#include<vector>
#include<QString>
#include<set>
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
    Gestore& operator=(const Gestore&);
    unsigned int generaNuovoId() const;
    void addAttivita(Attivita* a);
    bool removeAttivita(unsigned int id);
    //per svuotare dopo salvataggio su json
    void svuota();
    const std::vector<Attivita*>& getAllAttivita() const;
    Attivita* getAttivitaById(unsigned int id) const;
    std::vector<Attivita*> filtra(const filtro::AbstractFilter& af) const;
    bool salva(const QString& nomeFile = "dati_salvati.json") const;
    bool carica(const QString& nomeFile = "dati_salvati.json");
    //aggiunto per avere tutti gli anni presenti, utile per la gui
    std::set<int> getAnniPresenti() const;
    //aggiunto per avere una occorrenza di ogni tag presente, sempre per la gui
    std::set<QString> getTagPresenti() const;

};
}
#endif // GESTORE_H
