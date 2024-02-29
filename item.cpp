// SPDX-License-Identifier: GPL-2.0-only
#include <QFont>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsScene>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QProcess>
#include <QStyleOption>
#include "item.h"
#include "settings.h"

Item::Item(QString name, char *path, QWidget *centralWidget, QMenu *menu) : m_icon(new QIcon(path))
{
    m_name = name;
    m_centralWidget = centralWidget;
    m_menu = menu;
    m_hover = false;

    setFlag(ItemIsMovable);
    setAcceptHoverEvents(true);
}

Item::~Item() { }

void Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_menu->popup(event->screenPos());
    m_menu->exec(m_menu->mapToGlobal(event->screenPos()));
}

QRectF Item::boundingRect() const
{
    return QRectF(0, 0, g.item.width, g.item.height);
}

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    // Hover
    if (m_hover) {
        painter->setBrush(g.item.color.hover);
        painter->drawRect(boundingRect());
    }

    // Icon
    int offset = (g.item.width - g.item.iconSize) / 2.0;
    QRect target(offset, offset, g.item.iconSize, g.item.iconSize);
    QRect source(0, 0, g.item.iconSize, g.item.iconSize);
    painter->drawPixmap(target, m_icon->pixmap(QSize(g.item.iconSize, g.item.iconSize)), source);

    // Text
    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(g.core.fontPointSize);
    painter->setFont(font);
    painter->setPen(g.item.color.font);
    QRect rect(0, 0, g.item.width, g.item.height - g.item.spacing);
    QFontMetrics metrics(font);
    QString editedText = metrics.elidedText(m_name, Qt::ElideRight, rect.width());
    painter->drawText(rect, Qt::AlignCenter | Qt::AlignBottom, editedText);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Item::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_hover = true;
    update();
}

void Item::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_hover = false;
    update();
}

BackgroundItem::BackgroundItem(int width, int height)
{
    m_width = width;
    m_height = height;
}

BackgroundItem::~BackgroundItem() { }

QRectF BackgroundItem::boundingRect() const
{
    // Adjust for hard-coded margins in QGraphicsScene
    int width = m_width - 2;
    int height = m_height - 2;
    return QRectF(0.5, 0.5, width - 1.0, height - 1.0);
}

void BackgroundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // Panel background
    painter->setBrush(g.desktop.color.background);
    painter->setPen(g.desktop.color.background);
    painter->drawRect(boundingRect());

    if (getenv("IDESK_DEBUG")) {
        // Draw border to check it is pixel perfect with edge of screen
        QPen pen(Qt::red);
        pen.setStyle(Qt::SolidLine);
        pen.setWidth(1.0);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }
}
