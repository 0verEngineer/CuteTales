
#include "MainWindow.h"
#include "init.h"
#include "ui/MainWidget.h"
#include "dialogs/settings/SettingsDialog.h"
#include "dialogs/info/InfoDialog.h"

#include <ApplicationManager.h>
#include <qwidget.h>
#include <qgridlayout.h>
#include <qthread.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qmenu.h>
#include <qmenubar.h>

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent) {
    auto appManager = ApplicationManager::getInstance();
    appManager->setMainWindow(this);

    auto* app = dynamic_cast<QApplication *>(QApplication::instance());
    initTheme(app, winId());

    setWindowTitle(tr("CuteTales"));

    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);

    QThread::currentThread()->setObjectName("mainThread");

    setupMainToolBar();
    createMenuBar();
}

MainWindow::~MainWindow() {
    auto appManager = ApplicationManager::getInstance();
    endMainToolBar();

    delete infoDialog;
    infoDialog = nullptr;
    delete settingsDialog;
    settingsDialog = nullptr;

    appManager->setMainWindow(nullptr);
}

void MainWindow::toolBarSettingsButtonClicked() {
    if (!settingsDialog)
        settingsDialog = new SettingsDialog();

    settingsDialog->showDialog();
}


void MainWindow::toolBarInfoButtonClicked() {
    if (!infoDialog)
        infoDialog = new InfoDialog();

    infoDialog->showDialog();
}

void MainWindow::setupMainToolBar() {
    mainToolBar = new QToolBar(this);
    mainToolBar->setMovable(true);
    mainToolBar->setToolTipDuration(0);

    // SettingsButton
    settingsButton = new QToolButton(mainToolBar);
    settingsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    actions.settingsAction = new QAction(
                QIcon::fromTheme("preferences-system-symbolic"),
                tr("Settings"),
                settingsButton
    );
    settingsButton->addAction(actions.settingsAction);
    settingsButton->setDefaultAction(actions.settingsAction);
    settingsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainToolBar->addWidget(settingsButton);

    // InfoButton
    infoButton = new QToolButton(mainToolBar);
    infoButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    actions.infoAction = new QAction(
                QIcon::fromTheme("help-about-symbolic"),
                tr("Info"),
                infoButton
    );
    infoButton->addAction(actions.infoAction);
    infoButton->setDefaultAction(actions.infoAction);
    infoButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    mainToolBar->addWidget(infoButton);

    addToolBar(Qt::TopToolBarArea, mainToolBar);

    connect(actions.settingsAction, &QAction::triggered, this, &MainWindow::toolBarSettingsButtonClicked);
    connect(actions.infoAction, &QAction::triggered, this, &MainWindow::toolBarInfoButtonClicked);

}

void MainWindow::endMainToolBar() {
    disconnect(actions.settingsAction, &QAction::triggered, this, &MainWindow::toolBarSettingsButtonClicked);
    disconnect(actions.infoAction, &QAction::triggered, this, &MainWindow::toolBarInfoButtonClicked);
}

void MainWindow::changeEvent(QEvent* e) {
    // Todo: still needed?
/*#ifdef Q_OS_MACX
    if ( e->type() == QEvent::PaletteChange )
    {
        if (macIsInDarkTheme())
        {
            QIcon::setThemeName(ICONTHEMES.DARK);
        }
        else
        {
            QIcon::setThemeName(ICONTHEMES.LIGHT);
        }
    }
#endif*/
    QMainWindow::changeEvent(e);

}

void MainWindow::closeEvent(QCloseEvent* e) {
    QMainWindow::closeEvent(e);
}

void MainWindow::createMenuBar() {
    menuBar = new QMenuBar(this);
    this->setMenuBar(menuBar);

    fileMenu = new QMenu(tr("File"), menuBar);

    menuBar->addMenu(fileMenu);

    // Example:
    //fileMenu->addAction(actions.openAct);
}


