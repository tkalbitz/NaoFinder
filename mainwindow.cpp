/*
 * NaoFinder - Make robots visible
 * Copyright 2012-2013 Tobias Kalbitz.
 * Subject to the AGPL, version 3.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robotwidget.h"
#include "infocast.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* widget = new QWidget();
    panelLayout = new QVBoxLayout(widget);
    ui->scrollArea->setWidget(widget);
    createUdpSocket();
    createTrayIcon();

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

void MainWindow::createTrayIcon()
{
    QIcon icon(":/images/robot.png");
    setWindowIcon(icon);

    QAction* quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(icon);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::createUdpSocket()
{
    groupAdress = QHostAddress("230.0.0.1");

    udpSocket = new QUdpSocket(this);
    if(!udpSocket->bind(5880, QUdpSocket::ShareAddress)) {
        qDebug("Bind failed!");
    }

    QList<QNetworkInterface> if_list = QNetworkInterface::allInterfaces();
    for(int i = 0 ; i < if_list.size(); ++i) {
        QNetworkInterface this_iface = if_list.at(i);
        QNetworkInterface::InterfaceFlags if_flags = this_iface.flags();

        // skip internal and down ifaces
        if(if_flags & QNetworkInterface::IsPointToPoint ||
           ! this_iface.CanMulticast)
            continue;

        qDebug() << "Join Multicast Group: " << this_iface.humanReadableName();
        if(!udpSocket->joinMulticastGroup(groupAdress, this_iface)) {
            qDebug() << "Join Multicast Group failed! " << this_iface.humanReadableName() << " " << udpSocket->errorString();
        }
    }

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void MainWindow::readPendingDatagrams()
{
    qDebug() << "pending packet\n";
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        Infocast infocast;
        if(infocast.parse(datagram)) {
            qDebug() << "recv infocast\n";
            processInfocast(infocast);
        }
    }
}

void MainWindow::processInfocast(Infocast& i)
{
    if(!panelMap.contains(i.lanMac)) {
        RobotWidget* r = new RobotWidget();
        panelLayout->addWidget(r);
        panelMap[i.lanMac] = r;
    }

    RobotWidget* r = panelMap[i.lanMac];
    r->update(i);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    savedGeometry = geometry();
    hide();
    event->ignore();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if(isHidden()) {
            show();
            setGeometry(savedGeometry);
        } else {
            savedGeometry = geometry();
            hide();
        }
        break;
    default:
        ;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
