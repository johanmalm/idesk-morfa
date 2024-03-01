// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <QGraphicsView>
#include "application.h"
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
    void initApplications();
    void updateDesktop();
    void createActions();
    void createItemContextMenu();

    QList<QSharedPointer<Application>> m_applications;
    QWidget *m_parent;
    QMenu *m_itemContextMenu;
    QGraphicsScene m_scene;

    struct fd_icon_database *m_fd_icon_database;

    QAction *m_openAct;
    QAction *m_exitAct;
};
