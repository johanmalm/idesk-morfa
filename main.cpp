// SPDX-License-Identifier: GPL-2.0-only
#include <QApplication>
#include "mainwindow.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    QCoreApplication::setOrganizationName("idesk-morfa");
    QCoreApplication::setApplicationName("idesk");

    MainWindow win;
    win.show();

    return app.exec();
}
