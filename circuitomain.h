#ifndef CIRCUITOMAIN_H
#define CIRCUITOMAIN_H

#include <QMainWindow>

namespace Ui {
class CircuitoMain;
}

class CircuitoMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit CircuitoMain(QWidget *parent = 0);
    ~CircuitoMain();

private:
    Ui::CircuitoMain *ui;
};

#endif // CIRCUITOMAIN_H
