// SPDX-License-Identifier: GPL-2.0-only
#pragma once

#include <QColor>

struct Globals {
    struct {
        int fontPointSize;
    } core;

    struct {
        int padding;
        int spacing; // between items
        struct {
            QColor background;
        } color;
    } desktop;

    struct {
        int width;
        int height;
        int iconSize;
        int spacing;
        struct {
            QColor hover;
            QColor font;
        } color;
    } item;
};

extern Globals g;

void initSettings(void);
