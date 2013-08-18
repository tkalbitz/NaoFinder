/*
 * NaoFinder - Make robots visible
 * Copyright 2012-2013 Tobias Kalbitz.
 * Subject to the AGPL, version 3.
 */

#include <QApplication>
#include <QtGui>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);
    QApplication a(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    MainWindow w;
    w.show();
    
    return a.exec();
}
