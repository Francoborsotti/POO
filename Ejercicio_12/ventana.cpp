#include "ventana.h"
#include "ui_ventana.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    , manager(new QNetworkAccessManager(this)) // Inicializar manager
{
    ui->setupUi(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(resultado(QNetworkReply*)));

    peticionTemperature();
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::peticionTemperature()
{
    QUrl url("https://api.open-meteo.com/v1/forecast?latitude=-31.4135&longitude=-64.181&hourly=temperature_2m&forecast_days=1");
    manager->get(QNetworkRequest(url));
}

void Ventana::resultado(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = doc.object();
        QJsonObject hourlyObj = jsonObj["hourly"].toObject();
        QJsonArray tempArray = hourlyObj["temperature_2m"].toArray();
        double temp = tempArray[0].toDouble();
        ui->lTemperatura->setText("Temperatura: " + QString::number(temp) + " °C");
    } else {
        ui->lTemperatura->setText("Error al obtener temp");
    }
    reply->deleteLater();
}
