/*
 * NaoFinder - Make robots visible
 * Copyright 2012-2013 Tobias Kalbitz.
 * Subject to the AGPL, version 3.
 */

#include "robotwidget.h"
#include "ui_robotwidget.h"

RobotWidget::RobotWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RobotWidget)
{
    ui->setupUi(this);
}

RobotWidget::~RobotWidget()
{
    delete ui;
}

void RobotWidget::update(const Infocast& i)
{
    ui->lblRobot->setText(i.robotName + " - " + i.lanMac);
    ui->txtLanIp->setText(i.lanIp);
    ui->txtWifiIp->setText(i.wifiIp);
    ui->lblActualCpuTemp->setText(QString::number(i.cpuTemp & 0xff) + QString(" C"));
    ui->batteryValue->setValue(abs(i.battery));
}
