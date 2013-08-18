#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtNetwork/QtNetwork>
#include <QMap>

#include "robotwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void readPendingDatagrams();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    
private:
    Ui::MainWindow *ui;

    QHostAddress groupAdress;
    QUdpSocket* udpSocket;

    QVBoxLayout* panelLayout;
    QSystemTrayIcon *trayIcon;
    QRect savedGeometry;

    QMap<QString, RobotWidget*> panelMap;

    void createUdpSocket();
    void createTrayIcon();
    void processInfocast(Infocast& i);
};

#endif // MAINWINDOW_H
