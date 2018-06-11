#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ardrone2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connect_drone(void);

private:
    Ui::MainWindow *ui;
    ArDrone2 *ardrone2;
};

#endif // MAINWINDOW_H
