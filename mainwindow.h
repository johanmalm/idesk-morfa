// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *m_centralWidget;
};
