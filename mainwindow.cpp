// SPDX-License-Identifier: GPL-2.0-only
#include <LayerShellQt/shell.h>
#include <LayerShellQt/window.h>
#include <QDebug>
#include <QGuiApplication>
#include <QLabel>
#include <QLayout>
#include <QStackedLayout>
#include <QMetaEnum>
#include <QWindow>
#include <QWidget>
#include <string>
#include "desktop.h"
#include "mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initSettings();

    // Init layer-shell
    LayerShellQt::Shell::useLayerShell();
    this->winId();
    QWindow *window = this->windowHandle();
    auto layerShell = LayerShellQt::Window::get(window);
    layerShell->setMargins({ 0, 0, 0, 0 });
    const auto layer = QMetaEnum::fromType<LayerShellQt::Window::Layer>();
    layerShell->setLayer(LayerShellQt::Window::Layer(layer.keyToValue("LayerBottom")));
    const QString panelAnchors = "AnchorTop|AnchorLeft|AnchorRight|AnchorBottom";
    const auto anchorEnums = QMetaEnum::fromType<LayerShellQt::Window::Anchor>();
    uint32_t anchors = 0;
    const auto stringList = panelAnchors.split(QLatin1Char('|'));
    for (const auto &value : stringList) {
        anchors |= anchorEnums.keyToValue(qPrintable(value));
    }
    layerShell->setAnchors((LayerShellQt::Window::Anchors)anchors);
    layerShell->setKeyboardInteractivity(LayerShellQt::Window::KeyboardInteractivity(0));

    // Let compositor decide where window goes rather than just going with ScreenFromQWindow()
    //    const auto screen = QMetaEnum::fromType<LayerShellQt::Window::ScreenConfiguration>();
    //    layerShell->setScreenConfiguration(
    //        LayerShellQt::Window::ScreenConfiguration(screen.keyToValue("ScreenFromCompositor")));

    setAttribute(Qt::WA_TranslucentBackground);

    // With FramelessWIndowHint we need to run labwc with
    // WLR_SCENE_DISABLE_VISIBILITY=1
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    m_centralWidget = new QWidget;
    setCentralWidget(m_centralWidget);

    QStackedLayout *layout = new QStackedLayout;
    m_centralWidget->setLayout(layout);

    Desktop *desktop = new Desktop(m_centralWidget);
    layout->addWidget(desktop);
}

MainWindow::~MainWindow() { }
