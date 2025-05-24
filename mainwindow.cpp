#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager(this))
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    QString imgPath = QCoreApplication::applicationDirPath() + "/img/";

    // Загрузка карты мира
    if (!loadImage(ui->mapLabel, imgPath + "world.jpg")) {
        qWarning() << "Карта мира не загружена!";
    }

    // Загрузка маркера МКС
    if (!loadImage(ui->issMarker, imgPath + "iss.png")) {
        qWarning() << "Маркер МКС не загружен!";
    }

    // Настройка таймера для обновления позиции
    connect(timer, &QTimer::timeout, this, &MainWindow::updateIssPosition);
    timer->start(3000);
}

bool MainWindow::loadImage(QLabel *label, const QString &path) {
    QPixmap pix(path);
    if (pix.isNull()) {
        label->setText("Image not found: " + path);
        return false;
    }
    label->setPixmap(pix.scaled(label->size(), Qt::KeepAspectRatio));
    return true;
}

void MainWindow::updateIssPosition() {
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://api.wheretheiss.at/v1/satellites/25544")));
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument json = QJsonDocument::fromJson(reply->readAll());
            QJsonObject issData = json.object();

            double lat = issData["latitude"].toDouble();
            double lng = issData["longitude"].toDouble();

            // Вывод координат для отладки
            qDebug() << "ISS Position - Lat:" << lat << "Lng:" << lng;

            // Преобразование в координаты label
            int x = (lng + 180) * (ui->mapLabel->width() / 360);
            int y = (90 - lat) * (ui->mapLabel->height() / 180);

            // Проверка границ
            x = qBound(0, x, ui->mapLabel->width());
            y = qBound(0, y, ui->mapLabel->height());

            ui->issMarker->move(x, y);
        }
        reply->deleteLater();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
