#include "ventana.h"
#include "./ui_ventana.h"
#include <QJsonDocument>
#include <QJsonObject>

const QString API_KEY = "";
const QString API_URL = "";

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
{
    ui->setupUi(this);
}

Ventana::~Ventana()
{
    delete ui;
}
