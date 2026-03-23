#include "gestore.h"
#include<algorithm>
namespace modello
{
Gestore::~Gestore()
{
    for(auto it=listaAttivita.begin(); it!=listaAttivita.end(); it++)
    {
        delete *it;
    }
}
Gestore::Gestore(const Gestore& g)
{
    for( Attivita* a:g.listaAttivita)
    {
        listaAttivita.push_back(a->clone());
    }
}
Gestore& Gestore::operator=(const Gestore& g)
{
    if(this!=&g)
    {
        for(Attivita* a:listaAttivita) delete a;
        listaAttivita.clear();
        for(const Attivita* a:g.listaAttivita) listaAttivita.push_back(a->clone());
    }
    return *this;
}
unsigned int Gestore::generaNuovoId() const
{
    unsigned int max=0;
    if(listaAttivita.size()==0) return 1;
    for(Attivita* a:listaAttivita) if(a->getID()>max) max=a->getID();
    return max+1;

}
void Gestore::addAttivita(Attivita* a)
{
    auto it=std::find(listaAttivita.begin(), listaAttivita.end(), a);
    if(it==listaAttivita.end()) listaAttivita.push_back(a);
}
//***** OCIO: ritorna true se trova l'attivita' e la rimuove, false se non presente (anche se la gui dovrebbe sapere gia' gli id presenti, ricorda di togliere il bool eventualmente)
bool Gestore::removeAttivita(unsigned int id)
{
    //unsigned int check=listaAttivita.size();
    //listaAttivita.erase(std::remove_if(listaAttivita.begin(), listaAttivita.end(), [id](Attivita* a){return a->getID()==id;}),listaAttivita.end()); non dealloca la memoria mannaggia a
    //return check==listaAttivita.size();
    auto it=listaAttivita.begin();
    for(; it!=listaAttivita.end()&&(*it)->getID()!=id; it++);
    if(it!=listaAttivita.end())
    {
        delete *it;
        listaAttivita.erase(it);
        return true;
    }
    return false;

}
//per svuotare dopo salvataggio su json
void Gestore::svuota()
{
    for(Attivita* a:listaAttivita) delete a;
    listaAttivita.clear();
}
const std::vector<Attivita*>& Gestore::getAllAttivita() const
{
    return listaAttivita;
}
//do per assunto che l'id passato sia dentro la lista
Attivita* Gestore::getAttivitaById(unsigned int id) const
{
    for(Attivita* a:listaAttivita) if(a->getID()==id) return a;
    return nullptr;
}
std::vector<Attivita*> Gestore::filtra(const AbstractFilter& af) const
{
    std::vector<Attivita*> aux;
    std::for_each(listaAttivita.begin(), listaAttivita.end(),
                  [&af, &aux](Attivita* a)
                  {
        if(af.filtra(a)) aux.push_back(a);
    });
    return aux;
}
}
