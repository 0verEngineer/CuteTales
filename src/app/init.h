#ifndef INIT_H
#define INIT_H

#include "ApplicationManager.h"
#include <QApplication>
#include <QTranslator>
#include <QDirIterator>


inline void initDirectory()
{
    const QString path = QDir::homePath() + "/.CuteTales/";
    QDir appDir = QDir(path);

    if (!appDir.exists())
    {
        QDir().mkdir(path);
    }

    const QString styleSheetPath = path + "styleSheets/";
    QDir styleSheetDir = QDir(styleSheetPath);

    if (!styleSheetDir.exists())
    {
        QDir().mkdir(styleSheetPath);
    }
}


inline void applyStyleSheet(QFile& styleSheet, QApplication* app)
{
    // Todo disabled, do we still need style sheets with newest QT and System Theming?
    /*
    if (styleSheet.exists() && styleSheet.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&styleSheet);
        app->setStyleSheet(stream.readAll());
        return;
    }
    else
    {
        qWarning() << "Stylesheet " << styleSheet.fileName() << " does not exist, switching to default";
        auto settings = ApplicationManager::getInstance()->getSettings();

        QString iconThemeToApply = "";
        if (SystemThemeDetector::getSystemTheme() == SYSTEMTHEMES.DARK)
        {
            settings->style.styleSheet = STYLESHEETS.DARK;
            iconThemeToApply = ICONTHEMES.DARK;
        }
        else
        {
            settings->style.styleSheet = STYLESHEETS.LIGHT;
            iconThemeToApply = ICONTHEMES.DARK;
        }

        QFile defaultStyleSheet(settings->style.styleSheet);
        if (defaultStyleSheet.exists() && defaultStyleSheet.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream stream(&defaultStyleSheet);
            app->setStyleSheet(stream.readAll());

            // Do not set the icon theme on Linux...
#ifndef Q_OS_LINUX
        settings->style.iconTheme = iconThemeToApply;
        QIcon::setThemeName(iconThemeToApply);
#endif

            return;
        }
    }*/
}


#ifdef Q_OS_WIN
inline void initThemeWindows(QApplication* app, WId winId)
{
    /*auto settings = ApplicationManager::getInstance()->getSettings();

    if (settings->style.styleSheet.toLower().contains("dark"))
    {
        setDarkTitleBarWindows(reinterpret_cast<HWND>(winId));
    }

    QFile styleSheet = QFile(settings->style.styleSheet);
    applyStyleSheet(styleSheet, app);

    // Always set the icon theme on windows because there are no freedesktop icons
    QIcon::setThemeName(settings->style.iconTheme);*/
}
#endif


#ifdef Q_OS_LINUX
inline void initThemeLinux(QApplication* app)
{
    /*auto settings = ApplicationManager::getInstance()->getSettings();

    if (settings->style.useIconThemeOnLinux)
        QIcon::setThemeName(settings->style.iconTheme);
    else
        QIcon::setFallbackThemeName(settings->style.iconTheme);

    QFile styleSheet = QFile(settings->style.styleSheet);
    applyStyleSheet(styleSheet, app);*/
}
#endif


#ifdef Q_OS_DARWIN
inline void initThemeMac(QApplication* app)
{
    /*auto settings = ApplicationManager::getInstance()->getSettings();
    // Qt on MacOS has proper dark and light themes
    QFile styleSheet = QFile(settings->style.styleSheet);
    applyStyleSheet(styleSheet, app);

    // Always set the icon theme on MacOS because there are no freedesktop icons
    QIcon::setThemeName(settings->style.iconTheme);*/
}
#endif


inline void initTheme(QApplication* app, WId winId, bool isChangeMode = false)
{
    // todo needed?
    /*if (!isChangeMode)
    {
        auto* windowIcon = new QIcon(":/org.OverEngineer.CuteTales.ico");
        if (!windowIcon->isNull() && !windowIcon->availableSizes().empty())
            QApplication::setWindowIcon(*windowIcon);
    }*/

#ifdef Q_OS_WIN
    initThemeWindows(app, winId);
#endif

#ifdef Q_OS_LINUX
    initThemeLinux(app);
#endif

#ifdef Q_OS_DARWIN
    initThemeMac(app);
#endif
}


inline void changeTheme(QString filePath, WId winID)
{
    /*auto appManager = ApplicationManager::getInstance();
    appManager->getSettings()->style.styleSheet = filePath;
    initTheme(static_cast<QApplication *>(QApplication::instance()), winID, true);*/
}


inline void initLanguages(QApplication* app)
{
    QTranslator* translator = new QTranslator(app); // Todo: is this a memory leak or does installTranslator take ownership?
    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for (const QString &locale : uiLanguages) {
        const QString baseName = "CuteTales_" + QLocale(locale).name();
        if (translator->load(":/i18n/" + baseName)) {
            QApplication::installTranslator(translator);
            break;
        }
    }
}

inline void initSettings()
{
    ApplicationManager::getInstance()->setSettings(QSharedPointer<Settings>(new Settings()));
}

inline void initResources()
{
    // todo check if needed
/*#ifdef Q_OS_WIN
    Q_INIT_RESOURCE(windows_icon);
#endif*/

    /*
    Q_INIT_RESOURCE(licenses);
    Q_INIT_RESOURCE(breeze);
    Q_INIT_RESOURCE(systemStyleSheet);
    */
}


inline void init(QApplication* app)
{
    initResources();
    initDirectory();
    initLanguages(app);
    initSettings();
}

#endif // INIT_H
