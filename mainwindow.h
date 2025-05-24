#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateIssPosition();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QTimer *timer;

    bool loadImage(QLabel *label, const QString &path);
};
#endif // MAINWINDOW_H
