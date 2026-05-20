#ifndef ABSTRACTVISTAATTIVITA_H
#define ABSTRACTVISTAATTIVITA_H

#include <QWidget>
#include"../modello/attivita.h"
#include<vector>
namespace gui {
class AbstractVistaAttivita : public QWidget
{
    Q_OBJECT
private:

public:
    AbstractVistaAttivita(QWidget *parent = nullptr);
    virtual ~AbstractVistaAttivita()=default;
    virtual void popolaAttivita(const std::vector<modello::Attivita*>& vec)=0;

//signals:
Q_SIGNALS:
    void attivitaSelezionata(modello::Attivita*);
};
}
#endif // ABSTRACTVISTAATTIVITA_H
