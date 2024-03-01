// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <QGraphicsItem>

#define PANEL_TYPE_BACKGROUND 1
#define PANEL_TYPE_TASK 2

class Item : public QGraphicsItem
{
public:
    Item(QString name, char *path, QString exec, QWidget *centralWidget, QMenu *menu);
    ~Item();
    enum { Type = UserType + PANEL_TYPE_TASK };
    int type() const override { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

protected:
#ifndef QT_NO_CONTEXTMENU
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
#endif
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;

private:
    QWidget *m_centralWidget;
    QString m_name;
    QString m_exec;
    QScopedPointer<QIcon> m_icon;
    bool m_hover;
    QMenu *m_menu;

public:
    // Getters
    QString clientName() const { return m_name; }
    QString exec() const { return m_exec; }
    bool hover() const { return m_hover; }
};

class BackgroundItem : public QGraphicsItem
{
public:
    BackgroundItem(int width, int height);
    ~BackgroundItem();
    enum { Type = UserType + PANEL_TYPE_BACKGROUND };
    int type() const override { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) Q_DECL_OVERRIDE;

private:
    int m_width;
    int m_height;
};
