#ifndef ACTIVITYVISITORINTERFACE_H
#define ACTIVITYVISITORINTERFACE_H

namespace modello
{
class Esame;
class Scadenza;
class Appuntamento;
class Sport;
class ActivityVisitorInterface
{
public:
    virtual ~ActivityVisitorInterface()=default;
    virtual void visit(Esame* e)=0;
    virtual void visit(Scadenza* s)=0;
    virtual void visit(Appuntamento* i)=0;
    virtual void visit(Sport* s)=0;
};
}
#endif // ACTIVITYVISITORINTERFACE_H
