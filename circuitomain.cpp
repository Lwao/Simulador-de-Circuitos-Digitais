#include "circuitomain.h"
#include "ui_circuitomain.h"

CircuitoMain::CircuitoMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CircuitoMain)
{
    ui->setupUi(this);
}

CircuitoMain::~CircuitoMain()
{
    delete ui;
}
