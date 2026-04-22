#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include "gui/barralateralewidget.h"
namespace gui
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);

private:
    BarraLateraleWidget* barraLaterale;
};
}
#endif // MAINWINDOW_H
