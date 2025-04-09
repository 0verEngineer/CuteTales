
#ifndef CUTETALES_APPLICATIONMANAGER_H
#define CUTETALES_APPLICATIONMANAGER_H

#include "qobject.h"
#include "qsharedpointer.h"
#include "Settings.h"


class MainWindow;


/**
 * ApplicationManager singleton, used to access global objects.
 * Keep in mind that this is not thread safe, if you need any global object in a thread, you have to pass it to the thread.
 */
class ApplicationManager : public QObject
{
    Q_OBJECT

private:
    ApplicationManager() = default;
    ~ApplicationManager() = default;

public:
    static ApplicationManager* getInstance()
    {
        static ApplicationManager instance;
        return &instance;
    }

public:
    QSharedPointer<Settings> getSettings()
    {
        return settings;
    }

    // Todo: this is a shared pointer, why should we set it?
    void setSettings(const QSharedPointer<Settings>& newSettings)
    {
        this->settings = newSettings;
    }

    // Todo: needed?
    MainWindow* getMainWindow()
    {
        return mainWindow;
    }

    // Todo: needed?
    void setMainWindow(MainWindow* newMainWindow)
    {
        this->mainWindow = newMainWindow;
    }

public:
    ApplicationManager(ApplicationManager const&) = delete;
    void operator=(ApplicationManager const&) = delete;

private:
    QSharedPointer<Settings> settings;
    MainWindow* mainWindow;
};

#endif //CUTETALES_APPLICATIONMANAGER_H
