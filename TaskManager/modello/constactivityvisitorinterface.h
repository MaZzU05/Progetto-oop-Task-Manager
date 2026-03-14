#ifndef CONSTACTIVITYVISITORINTERFACE_H
#define CONSTACTIVITYVISITORINTERFACE_H
namespace modello
{
class Esame;
class ConstActivityVisitorInterface
{
public:
    virtual ~ConstActivityVisitorInterface()=default;
    virtual void visit(const Esame* e)=0;
    //virtual void visit(Scadenza* s)=0;
    //virtual void visit(Impegni* i)=0;
};
}
#endif // CONSTACTIVITYVISITORINTERFACE_H
