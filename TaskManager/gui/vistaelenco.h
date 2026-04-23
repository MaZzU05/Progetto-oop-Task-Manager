#ifndef VISTAELENCO_H
#define VISTAELENCO_H

#include "abstractvistaattivita.h"
#include<QScrollArea>
#include<QVBoxLayout>
namespace gui
{
class VistaElenco : public AbstractVistaAttivita
{
    Q_OBJECT
private:
    //uso la scrooll area che mi da la possibilita' di avere una parte che occupa poco spazio e nella quale posso scorrere gli elementi all'interno, dato che puo' contenere solo un widget, ne creo uno che sara' il contenitore di tutte le attivita' che andro' a costruire in maniera polimorfa in base al tipo
    QScrollArea* areaScorrimento;
    QWidget* contenitoreCentrale;
    QVBoxLayout* layout;
    void setup();
public:
    VistaElenco(QWidget *parent = nullptr);
    void popolaAttivita(const std::vector<modello::Attivita*>& vec) override;
};
}
#endif // VISTAELENCO_H
