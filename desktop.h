// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <QGraphicsView>
#include "item.h"
#include "settings.h"

class Desktop : public QGraphicsView
{
    Q_OBJECT

public:
    Desktop(QWidget *parent = 0);
    ~Desktop();

private slots:
    void openApplication();
    void exit();

private:
    void updateDesktop();
    void createActions();
    void createItemContextMenu();
    QWidget *m_parent;
    QMenu *m_itemContextMenu;
    QGraphicsScene m_scene;

    struct fd_icon_database *m_fd_icon_database;

    QAction *m_openAct;
    QAction *m_exitAct;
};
