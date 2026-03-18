#ifndef CONSTACTIVITYVISITORINTERFACE_H
#define CONSTACTIVITYVISITORINTERFACE_H
namespace modello
{
class Esame;
class Scadenza;
class Appuntamento;
class ConstActivityVisitorInterface
{
public:
    virtual ~ConstActivityVisitorInterface()=default;
    virtual void visit(const Esame* e)=0;
    virtual void visit(const Scadenza* s)=0;
    virtual void visit(const Appuntamento* i)=0;
};
}
#endif // CONSTACTIVITYVISITORINTERFACE_H
