#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class InfoDialog;
class SettingsDialog;
class QToolButton;
class MainWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void toolBarSettingsButtonClicked();
    void toolBarInfoButtonClicked();

private:
    void setupMainToolBar();
    void endMainToolBar();
    void changeEvent(QEvent* e);
    void closeEvent(QCloseEvent* e);
    void createMenuBar();

public:
    struct Actions
    {
        QAction* settingsAction = nullptr;
        QAction* infoAction = nullptr;
    };
    Actions actions;

private:
    MainWidget* mainWidget = nullptr;

    SettingsDialog* settingsDialog = nullptr;
    InfoDialog* infoDialog = nullptr;
    QToolBar *mainToolBar = nullptr;

    QToolButton* settingsButton = nullptr;
    QToolButton* infoButton = nullptr;

    QMenuBar* menuBar = nullptr;
    QMenu* fileMenu = nullptr;
};

#endif
