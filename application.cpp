// SPDX-License-Identifier: GPL-2.0-only
#include <QDebug>
#include <QFile>
#include <QString>
#include "application.h"

Application::Application(QFile *f)
{
    bool inEntry = false;
    QTextStream in(f);
    while (!in.atEnd()) {
        QString line = in.readLine();

        if (line.contains("[Desktop Entry]")) {
            inEntry = true;
            continue;
        } else if (line.startsWith("[")) {
            inEntry = false;
            continue;
        }
        if (!inEntry) {
            continue;
        }

        // We're in [Desktop Entry] section
        if (line.startsWith("Name=")) {
            m_name = line.replace("Name=", "");
        } else if (line.startsWith("Icon=")) {
            m_icon = line.replace("Icon=", "");
        } else if (line.startsWith("Exec=")) {
            m_exec = line.replace("Exec=", "");
        }
    }
}

Application::~Application() { }
