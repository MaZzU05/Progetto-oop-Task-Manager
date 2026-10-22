#ifndef GESTOREOBSERVERINTERFACE_H
#define GESTOREOBSERVERINTERFACE_H
namespace modello
{
class Gestore;

class GestoreObserverInterface{
public:
    virtual ~GestoreObserverInterface()=default;
    virtual void notify(Gestore& gestore)=0;
};
}

#endif // GESTOREOBSERVERINTERFACE_H
