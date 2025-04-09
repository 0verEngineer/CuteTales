#include "StyleSettingsTab.h"
#include "app/init.h"
#include "app/ui/MainWindow.h"

#include "qcombobox.h"
#include "qstringlist.h"
#include "qdiriterator.h"
#include "qvariant.h"
#include "qlabel.h"


// Todo: Stylesheets still needed?
StyleSettingsTab::StyleSettingsTab(QWidget* parent)
    : QWidget{parent}
{
    auto appManager = ApplicationManager::getInstance();
    auto settings = appManager->getSettings();

    if (parent)
        this->setParent(parent);

    this->setLayout(this->layout);

    /*

    // UseStyleSheet Checkbox
#ifdef Q_OS_LINUX
    this->useIconThemeCB = new QCheckBox(this);
    this->layout->addWidget(this->useIconThemeCB, 0, 0);
    this->useIconThemeCB->setText(tr("Force IconTheme on Linux"));
    this->useIconThemeCB->setChecked(settings->style.useIconThemeOnLinux);
    connect(this->useIconThemeCB, &QCheckBox::toggled, this, &StyleSettingsTab::useIconThemeCheckboxChanged);
#endif

    // --- StyleSheetSelector ---
    QLabel* styleSheetSelectorLabel = new QLabel(this);
    styleSheetSelectorLabel->setText(tr("Stylesheet") + ":");
    this->layout->addWidget(styleSheetSelectorLabel, 1, 0);

    this->styleSheetSelector = new QComboBox(this);
    this->layout->addWidget(this->styleSheetSelector, 1, 1);

    // --- Add the 2 standard Styles to the list ---
    this->styleSheetSelector->addItem("CuteTales Dark", QVariant(STYLESHEETS.DARK));
    this->styleSheetSelector->addItem("CuteTales Light", QVariant(STYLESHEETS.LIGHT));
    this->styleSheetSelector->addItem("System", QVariant(STYLESHEETS.SYSTEM));

    QString styleSheetsPath = QDir::homePath() + "/.CuteTales/styleSheets/";

    // --- Iterate over stylesheet dir ---
    QDirIterator it(styleSheetsPath, QStringList() << "*.qss", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        it.next();
        this->styleSheetSelector->addItem(it.fileName(), QVariant(it.path() + it.fileName()));
    }

    styleSheetSelector->setCurrentIndex(styleSheetSelector->findData(settings->style.styleSheet));

    // --- IconThemeSelector ---
    QLabel* iconThemeSelectorLabel = new QLabel(this);
    iconThemeSelectorLabel->setText(tr("Icon Theme") + ":");
    this->layout->addWidget(iconThemeSelectorLabel, 2, 0);

    this->iconThemeSelector = new QComboBox(this);
    this->layout->addWidget(this->iconThemeSelector, 2, 1);

    this->iconThemeSelector->addItem(tr("Dark"), QVariant(ICONTHEMES.DARK));
    this->iconThemeSelector->addItem(tr("Light"), QVariant(ICONTHEMES.LIGHT));

    this->iconThemeSelector->setCurrentIndex(iconThemeSelector->findData(settings->style.iconTheme));

    iconThemeSelector->setToolTip(tr("Sometimes the Icontheme is only applied upon closing the Settings Window"));

    // --- FileViewModeSelector ---
    QLabel* fileViewModeSelectorLabel = new QLabel(this);
    fileViewModeSelectorLabel->setText(tr("File-View Mode") + ":");
    this->layout->addWidget(fileViewModeSelectorLabel, 3, 0);

    this->fileViewModeSelector = new QComboBox(this);
    this->layout->addWidget(this->fileViewModeSelector, 3, 1);

    this->fileViewModeSelector->addItem(tr("Icon view"), QVariant(FILEVIEWMODE.ICON));
    this->fileViewModeSelector->addItem(tr("List view"), QVariant(FILEVIEWMODE.LIST));

    this->fileViewModeSelector->setCurrentIndex(fileViewModeSelector->findData(settings->style.fileViewMode));

    // todo can this be done better? -> never connect in the child to the parent
    auto mainWindow = appManager->getMainWindow();
    if (mainWindow != nullptr)
    {
        connect(
                this->fileViewModeSelector,
                &QComboBox::currentIndexChanged,
                mainWindow,
                &MainWindow::fileViewModeChangedSlot
        );
    }

    // --- Connections ---
    connect(this->styleSheetSelector, &QComboBox::currentIndexChanged, this, &StyleSettingsTab::styleSheetSelectorChanged);
    connect(iconThemeSelector, &QComboBox::currentIndexChanged, this, &StyleSettingsTab::iconThemeSelectorChanged);

    */
}


StyleSettingsTab::~StyleSettingsTab()
{
  /*
    disconnect(this->styleSheetSelector, &QComboBox::currentIndexChanged, this, &StyleSettingsTab::styleSheetSelectorChanged);
    disconnect(iconThemeSelector, &QComboBox::currentIndexChanged, this, &StyleSettingsTab::iconThemeSelectorChanged);

#ifdef Q_OS_LINUX
    disconnect(this->useIconThemeCB, &QCheckBox::toggled, this, &StyleSettingsTab::useIconThemeCheckboxChanged);
#endif

   */
}


void StyleSettingsTab::useIconThemeCheckboxChanged(bool checked)
{
    //ApplicationManager::getInstance()->getSettings()->style.useIconThemeOnLinux = checked;
    //initTheme(static_cast<QApplication *>(QApplication::instance()), winId());
}


void StyleSettingsTab::styleSheetSelectorChanged(int index)
{
  /*
    QString theme = this->styleSheetSelector->itemData(index).value<QString>();
    changeTheme(theme, winId());
    resetIconSelector(theme);

   */
}


void StyleSettingsTab::iconThemeSelectorChanged(int index)
{
  /*
    QString iconTheme = iconThemeSelector->itemData(index).toString();
    ApplicationManager::getInstance()->getSettings()->style.iconTheme = iconTheme;
    QIcon::setThemeName(iconTheme);

   */
}


void StyleSettingsTab::resetIconSelector(QString styleSheet)
{
  /*
    if (styleSheet == STYLESHEETS.DARK || styleSheet.toLower().contains("dark"))
        iconThemeSelector->setCurrentIndex(0);
    if (styleSheet == STYLESHEETS.LIGHT || styleSheet.toLower().contains("light"))
        iconThemeSelector->setCurrentIndex(1);

   */
}

