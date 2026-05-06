#ifndef GESTORE_H
#define GESTORE_H
#include "Filtri/abstractfilter.h"
#include "gestoreobserverinterface.h"
#include"Filtri/filtrocongiuntivo.h"
#include "attivita.h"
#include "libretto.h"
#include <QString>
#include <set>
#include <vector>
namespace modello {
class Gestore {
private:
  std::vector<Attivita *> listaAttivita;
  std::vector<GestoreObserverInterface*> observers;
  filtro::FiltroCongiuntivo* filtroAttivo=nullptr;
  std::vector<Attivita *> filtra(const filtro::AbstractFilter &af) const;
  Libretto libretto;
  void notifyObserves();

public:
  Gestore() : libretto(0, "", listaAttivita) {}
  ~Gestore();
  // rule of three
  Gestore(const Gestore &);
  Gestore &operator=(const Gestore &);
  void registraObserver(GestoreObserverInterface* observer);
  void setFiltro(filtro::FiltroCongiuntivo* nuovoFiltro);
  std::vector<Attivita*> getAttivitaFiltrate() const;
  unsigned int generaNuovoId() const;
  void addAttivita(Attivita *a);
  bool removeAttivita(unsigned int id);
  Libretto &getLibretto();
  void inizializzaLibretto(const QString& corso, int cfu);
  // per svuotare dopo salvataggio su json
  void svuota();
  const std::vector<Attivita *> &getAllAttivita() const;
  Attivita *getAttivitaById(unsigned int id) const;
  bool salva(const QString &nomeFile = "dati_salvati.json") const;
  bool carica(const QString &nomeFile = "dati_salvati.json");
  // aggiunto per avere tutti gli anni presenti, utile per la gui
  std::set<int> getAnniPresenti() const;
  // aggiunto per avere una occorrenza di ogni tag presente, sempre per la gui
  std::set<QString> getTagPresenti() const;
};
} // namespace modello
#endif // GESTORE_H
