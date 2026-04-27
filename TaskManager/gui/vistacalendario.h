#ifndef VISTACALENDARIO_H
#define VISTACALENDARIO_H

#include <QObject>
#include <QWidget>
#include<QCalendarWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include "abstractvistaattivita.h"
namespace gui
{
class vistaCalendario : public AbstractVistaAttivita
{
public:
    vistaCalendario();
};
}
#endif // VISTACALENDARIO_H
