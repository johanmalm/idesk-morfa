// SPDX-License-Identifier: GPL-2.0-only
#pragma once
#include <QString>
#include <QFile>

class Application
{
public:
    Application(QFile *f);
    ~Application();

private:
    QString m_name;
    QString m_icon;
    QString m_exec;

public:
    // Getters
    QString name() const { return m_name; }
    QString icon() const { return m_icon; }
    QString exec() const { return m_exec; }
};
