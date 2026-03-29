#ifndef JSONSAVERVISITOR_H
#define JSONSAVERVISITOR_H
#include"constactivityvisitorinterface.h"
#include<QJsonObject>
#include"attivita.h"
namespace modello
{
class JsonSaverVisitor: public ConstActivityVisitorInterface
{
private:
    QJsonObject daSalvare;
    void preparaBase(const Attivita* a);
public:
    JsonSaverVisitor()=default;
    void visit(const Esame* e) override;
    void visit(const Scadenza* s) override;
    void visit(const Appuntamento* i) override;
    void visit(const Sport* s) override;
    QJsonObject getJsonObject() const;
};
}
#endif // JSONSAVERVISITOR_H
