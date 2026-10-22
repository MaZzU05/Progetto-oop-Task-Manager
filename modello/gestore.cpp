#include "gestore.h"
#include "appuntamento.h"
#include "esame.h"
#include "jsonsavervisitor.h"
#include "scadenza.h"
#include "sport.h"
#include <QFile>
#include <QJsonDocument>
#include <QTextStream>
#include <QtCore/qjsonarray.h>
#include <algorithm>

namespace modello {

bool Gestore::haModificheNonSalvate() const {
  return modificheNonSalvate;
}

void Gestore::setModificheNonSalvate(bool stato) {
  modificheNonSalvate = stato;
}

Gestore::~Gestore() {
  for (auto it = listaAttivita.begin(); it != listaAttivita.end(); it++) {
    delete *it;
  }
  delete filtroAttivo;
}
Gestore::Gestore(const Gestore &g) : libretto(g.libretto.getCfu(), g.libretto.getCorsoLaurea(), listaAttivita) {
    for (Attivita *a : g.listaAttivita) {
        listaAttivita.push_back(a->clone());
    }
}
Gestore &Gestore::operator=(const Gestore &g) {
  if (this != &g) {
    libretto = g.libretto;
    for (Attivita *a : listaAttivita)
      delete a;
    listaAttivita.clear();
    for (const Attivita *a : g.listaAttivita)
      listaAttivita.push_back(a->clone());
    delete filtroAttivo;
    filtroAttivo=nullptr;
  }
  return *this;
}
unsigned int Gestore::generaNuovoId() const {
  unsigned int max = 0;
  if (listaAttivita.size() == 0)
    return 1;
  for (Attivita *a : listaAttivita)
    if (a->getID() > max)
      max = a->getID();
  return max + 1;
}
void Gestore::addAttivita(Attivita *a) {
  auto it = std::find(listaAttivita.begin(), listaAttivita.end(), a);
  if (it == listaAttivita.end())
  {
    listaAttivita.push_back(a);
    modificheNonSalvate = true;
      //notifico
      notifyObserves();
  }
}
bool Gestore::removeAttivita(unsigned int id) {
  // unsigned int check=listaAttivita.size();
  // listaAttivita.erase(std::remove_if(listaAttivita.begin(),
  // listaAttivita.end(), [id](Attivita* a){return
  // a->getID()==id;}),listaAttivita.end()); non dealloca la memoria mannaggia a me
  // return check==listaAttivita.size();
  auto it = listaAttivita.begin();
  for (; it != listaAttivita.end() && (*it)->getID() != id; it++);
  if (it != listaAttivita.end()) {
    delete *it;
    listaAttivita.erase(it);
    modificheNonSalvate = true;
    //notifico
    notifyObserves();
    return true;
  }
  return false;
}
// per svuotare dopo salvataggio su json
void Gestore::svuota() {
  for (Attivita *a : listaAttivita)
    delete a;
  listaAttivita.clear();
}
const std::vector<Attivita *> &Gestore::getAllAttivita() const {
  return listaAttivita;
}
// do per assunto che l'id passato sia dentro la lista
Attivita *Gestore::getAttivitaById(unsigned int id) const {
  for (Attivita *a : listaAttivita)
    if (a->getID() == id)
      return a;
  return nullptr;
}
std::vector<Attivita *>
Gestore::filtra(const filtro::AbstractFilter &af) const {
  std::vector<Attivita *> aux;
  std::for_each(listaAttivita.begin(), listaAttivita.end(),
                [&af, &aux](Attivita *a) {
                  if (af.filtra(a))
                    aux.push_back(a);
                });
  return aux;
}
bool Gestore::salva(const QString &nomeFile) const {
  // aggiungo la parte per i dati del libretto, metto tutto in un QJsonObject
  QJsonObject daSalvare;
  // dati del libretto
  QJsonObject infoLibretto;
  infoLibretto["corsoDiLaurea"] = libretto.getCorsoLaurea();
  infoLibretto["cfu_totali"] = static_cast<int>(libretto.getCfu());
  daSalvare["info_laurea"] = infoLibretto;
  QJsonArray arrayAttivita;
  JsonSaverVisitor visitor;
  for (Attivita *a : listaAttivita) {
    a->accept(&visitor);
    arrayAttivita.append(visitor.getJsonObject());
  }
  daSalvare["lista_attivita"] = arrayAttivita;
  QJsonDocument doc(daSalvare); //"contenitore" dove appoggio il QJsonObject,necessario prima del salvataggio va trasformato in sequenza di byte, uso indented che occupa piu' spazio ma e' piu' leggibile, almeno per essere sicuro funzioni correttamente
  QByteArray datiJson = doc.toJson(QJsonDocument::Indented);
  // apro il file
  QFile file(nomeFile);
  // controllo se l'apertura funziona, altrimenti ritorno falso
  if (file.open(QIODevice::WriteOnly)) {
    file.write(datiJson);
    file.close();
    modificheNonSalvate = false;
    return true;
  }
  return false;
}
bool Gestore::carica(const QString &nomeFile) {
  // seguiro il processo inverso al salvataggio
  // svuoto le attivita' attualmente in ram, se no avrei duplicati
  svuota();
  QFile file(nomeFile);
  if (file.open(QIODevice::ReadOnly)) {
    QByteArray datiJson = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(datiJson);
    QJsonObject principale = doc.object();
    QJsonObject info = principale["info_laurea"].toObject();
    libretto.setCorsoLaurea(info["corsoDiLaurea"].toString());
    libretto.setCfu(info["cfu_totali"].toInt());
    // passo alla lista di attivita
    QJsonArray daCaricare = principale["lista_attivita"].toArray();
    for (auto it = daCaricare.begin(); it != daCaricare.end(); it++) {
      QJsonObject aux = (*it).toObject();
      QString tipo = aux["Tipo"].toString();
      if (tipo != "Esame" && tipo != "Scadenza" && tipo != "Appuntamento" &&
          tipo != "Sport") {
        svuota();
        file.close();
        return false;
      }
      // gli attributi della base li estrago gia', per rispettare il principio
      // DRY so che alcuni cast sono impliciti ma li esplicito per leggibilita'
      QString title = aux["title"].toString();
      unsigned int id = static_cast<unsigned int>(aux["id"].toInt());
      QString note = aux["note"].toString();
      bool complete = aux["complete"].toBool();
      // leggo dalla stringa in formato iso, converte automaticamente in data
      QDateTime dataCreazione =
          QDateTime::fromString(aux["dataCreazione"].toString(), Qt::ISODate);
      QDateTime dataFine =
          QDateTime::fromString(aux["dataFine"].toString(), Qt::ISODate);
      unsigned int durata = static_cast<unsigned int>(aux["durata"].toInt());
      Priority priorita = static_cast<Priority>(aux["priorita"].toInt());
      if (tipo == "Esame") {

        unsigned int cfu = static_cast<unsigned int>(aux["cfu"].toInt());
        unsigned int voto = static_cast<unsigned int>(aux["voto"].toInt());
        bool lode = aux["lode"].toBool();
        QString sede = aux["sede"].toString();
        Esame *e = new Esame(title, id, note, sede, cfu, dataFine, durata,
                             complete, priorita);
        e->changeDataCreazione(dataCreazione);
        if(voto!=0)
            e->setVoto(voto);
        e->modifyLode(lode);
        QJsonArray tempTag = aux["tag"].toArray();
        for (auto it = tempTag.begin(); it != tempTag.end(); it++) {
          e->addTag(it->toString());
        }
        QJsonArray tempProf = aux["professori"].toArray();
        for (auto it = tempProf.begin(); it != tempProf.end(); it++) {
          e->addProfessor(it->toString());
        }
        addAttivita(e);

      } else if (tipo == "Scadenza") {
        unsigned int giorniPreavviso =
            static_cast<unsigned int>(aux["giorniPreavviso"].toInt());
        Scadenza *s = new Scadenza(title, id, note, dataFine, giorniPreavviso,
                                   durata, complete, priorita);
        s->changeDataCreazione(dataCreazione);
        QJsonArray tempTag = aux["tag"].toArray();
        for (auto it = tempTag.begin(); it != tempTag.end(); it++) {
          s->addTag(it->toString());
        }
        QJsonArray tempToDo = aux["todoList"].toArray();
        for (auto it = tempToDo.begin(); it != tempToDo.end(); it++) {
          QJsonObject sottoTask = it->toObject();
          s->addPassaggio(sottoTask["descrizione"].toString());
          s->setPassaggioCompletato(sottoTask["descrizione"].toString(),
                                    sottoTask["completa"].toBool());
        }
        addAttivita(s);

      } else if (tipo == "Appuntamento") {
        QString luogo = aux["luogo"].toString();
        bool inPresenza = aux["inPresenza"].toBool();
        Appuntamento *a =
            new Appuntamento(title, id, note, dataFine, luogo, durata,
                             inPresenza, complete, priorita);
        a->changeDataCreazione(dataCreazione);
        QJsonArray tempTag = aux["tag"].toArray();
        for (auto it = tempTag.begin(); it != tempTag.end(); it++) {
          a->addTag(it->toString());
        }
        QJsonArray tempPartecipanti = aux["partecipanti"].toArray();
        for (auto it = tempPartecipanti.begin(); it != tempPartecipanti.end();
             it++) {
          a->addPartecipante(it->toString());
        }
        addAttivita(a);

      } else if (tipo == "Sport") {
        QString luogo = aux["luogo"].toString();
        QDate dataInizio =
            QDate::fromString(aux["dataInizio"].toString(), Qt::ISODate);
        Sport *s = new Sport(title, id, note, dataFine, durata, dataInizio,
                             luogo, complete, priorita);
        s->changeDataCreazione(dataCreazione);
        QJsonArray tempTag = aux["tag"].toArray();
        for (auto it = tempTag.begin(); it != tempTag.end(); it++) {
          s->addTag(it->toString());
        }
        QJsonArray tempGiorniSport = aux["giorni_sport"].toArray();
        for (auto it = tempGiorniSport.begin(); it != tempGiorniSport.end();
             it++) {
          s->setGiornoSettimana(static_cast<Qt::DayOfWeek>(it->toInt()));
        }
        addAttivita(s);
      }
    }
    file.close();
    modificheNonSalvate = false;
    //notifico
    notifyObserves();
    return true;
  }
  return false;
}
std::set<int> Gestore::getAnniPresenti() const {
  std::set<int> aux;
  std::for_each(
      listaAttivita.begin(), listaAttivita.end(),
      [&aux](Attivita *a) -> void { aux.insert(a->getDate().date().year()); });
  return aux;
}
std::set<QString> Gestore::getTagPresenti() const {
  std::set<QString> aux;
  for (Attivita *a : listaAttivita) {
    std::vector<QString> temp = a->getAllTag();
    std::for_each(temp.begin(), temp.end(),
                  [&aux](const QString &tag) -> void { aux.insert(tag); });
  }
  return aux;
}

Libretto& Gestore::getLibretto() { return libretto; }

void Gestore::registraObserver(GestoreObserverInterface* observer)
{
    observers.push_back(observer);
}

void Gestore::notifyObserves()
{
    //ciclo di notifica
    for(auto it=observers.begin(); it!=observers.end(); it++)
    {
        (*it)->notify(*this);
    }
}

void Gestore::setFiltro(filtro::FiltroCongiuntivo* nuovoFiltro)
{
    //se filtro allocato in memoria, lo elimino, poi copio il nuovo
    if(filtroAttivo)
        delete filtroAttivo;
    filtroAttivo=nuovoFiltro;
    //notifico
    notifyObserves();
}
std::vector<Attivita*> Gestore::getAttivitaFiltrate() const
{
    //se il filtro e' null significa che non ci sono filtri, restituisco tutta la lista
    if(filtroAttivo==nullptr)
        return listaAttivita;
    return filtra(*filtroAttivo);
}

void Gestore::inizializzaLibretto(const QString& corso, int cfu)
{
    libretto.setCorsoLaurea(corso);
    libretto.setCfu(cfu);
    modificheNonSalvate = true;
    //notifico
    notifyObserves();

}
} // namespace modello
