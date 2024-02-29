// SPDX-License-Identifier: GPL-2.0-only
#include <QDebug>
#include <QSettings>
#include <QString>
#include <QVariant>
#include "settings.h"

Globals g;

static void setValueIfMissing(QSettings *s, QString key, QString value)
{
    if (!s->contains(key))
        s->setValue(key, value);
}

static int initInt(QSettings *s, QString key, QString value)
{
    setValueIfMissing(s, key, value);
    return s->value(key).toInt();
}

static QString initString(QSettings *s, QString key, QString value)
{
    setValueIfMissing(s, key, value);
    return s->value(key).toString();
}

static QColor initColor(QSettings *s, QString key, QString hexValue)
{
    setValueIfMissing(s, key, hexValue);
    return QColor(s->value(key).toString());
}

void initSettings(void)
{
    QSettings s;

    g.core.fontPointSize = initInt(&s, "core/fontPointSize", "9");

    // Allow plenty of padding of panels
    g.desktop.padding = initInt(&s, "desktop/padding", "25");
    g.desktop.spacing = initInt(&s, "desktop/spacing", "15");
    g.desktop.color.background = initColor(&s, "desktop/color-background", "#ff21333b");

    g.item.iconSize = initInt(&s, "item/iconSize", "48");
    g.item.spacing = initInt(&s, "item/spacing", "10");
    g.item.color.hover = initColor(&s, "item/color-hover", "#18aaaaaa");
    g.item.color.font = initColor(&s, "item/color-font", "#ffeeeeee");

    // Derived variables
    int textHeight = 1.5 * g.core.fontPointSize;
    g.item.width = g.item.spacing * 2 + g.item.iconSize;
    g.item.height = g.item.spacing * 3 + g.item.iconSize + textHeight;
}
