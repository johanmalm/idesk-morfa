// SPDX-License-Identifier: GPL-2.0-only
#include <QDebug>
#include <QGuiApplication>
#include <QTextStream>
#include <QtWidgets>
#include <unistd.h>
#include "desktop.h"
extern "C" {
#include "fdicons.h"
}
#include "settings.h"

Desktop::Desktop(QWidget *parent) : QGraphicsView(parent)
{
    m_parent = parent;
    setScene(&m_scene);

    int width = QGuiApplication::primaryScreen()->geometry().width();
    int height = QGuiApplication::primaryScreen()->geometry().height();
    m_scene.setSceneRect(0, 0, width, height);
    m_scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color: transparent;");

    BackgroundItem *p = new BackgroundItem(width, height);
    m_scene.addItem(p);
    p->setPos(0, 0);

    createActions();
    createItemContextMenu();

    // Create icons
    m_fd_icon_database = fd_icon_database_create();
    fd_icon_database_add_default_paths(m_fd_icon_database);
    QVector<QString> names = { "xterm", "hexchat", "firefox", "foot" };
    foreach (QString name, names) {
        struct fd_icon *fd_icon = fd_icon_database_get_icon(m_fd_icon_database, 48,
                                                            name.toLatin1().data(), "folder", NULL);
        Item *item = new Item(name, fd_icon->path, m_parent, m_itemContextMenu);
        m_scene.addItem(item);
        fd_icon_destroy(fd_icon);
    }

    updateDesktop();
}

Desktop::~Desktop()
{
    fd_icon_database_destroy(m_fd_icon_database);
}

void Desktop::updateDesktop()
{
    // Set the icon positions
    int i = 0;
    foreach (QGraphicsItem *item, items()) {
        if (Item *p = qgraphicsitem_cast<Item *>(item)) {
            int y = g.desktop.padding + i * (g.item.height + g.desktop.spacing);
            int x = g.desktop.padding;
            p->setPos(x, y);
            i++;
        }
    }
}

void spawn(QString command)
{
    pid_t pid = fork();
    if (!pid) {
        execl("/bin/sh", "sh", "-c", command.toLatin1().data(), (void *)NULL);
        exit(1);
    }
}

void Desktop::openApplication()
{
    foreach (QGraphicsItem *item, items()) {
        if (Item *p = qgraphicsitem_cast<Item *>(item)) {
            if (!p->hover())
                continue;
            qDebug() << "exec" << p->clientName();
            spawn(p->clientName());
            break;
        }
    }
}

void Desktop::exit()
{
    QCoreApplication::quit();
}

void Desktop::createActions()
{
    m_openAct = new QAction("&Open", this);
    connect(m_openAct, &QAction::triggered, this, &Desktop::openApplication);
    m_exitAct = new QAction("&Exit", this);
    connect(m_exitAct, &QAction::triggered, this, &Desktop::exit);
}

void Desktop::createItemContextMenu()
{
    m_itemContextMenu = new QMenu("Item Context Menu", m_parent);
    m_itemContextMenu->addAction(m_openAct);
    m_itemContextMenu->addAction(m_exitAct);
}
