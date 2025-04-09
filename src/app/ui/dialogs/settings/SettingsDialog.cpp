#include "SettingsDialog.h"

#include <QBoxLayout>
#include <QTabWidget>

// todo theming
/*#ifdef Q_OS_WIN
#include "../../windows/titleBar.h"
#endif*/


SettingsDialog::SettingsDialog(QWidget* parent)
{
    if (parent)
        this->setParent(parent);

    // todo theming
/*#ifdef Q_OS_WIN
    setDarkTitleBarWindows(reinterpret_cast<HWND>(this->winId()));
#endif*/

    this->setWindowTitle(tr("Settings"));
    this->setMinimumSize(600, 420);

    this->layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);

    this->tabWidget = new QTabWidget(this);
    this->layout->addWidget(this->tabWidget);

    // General Settings (does not need to be constructed new every time)
    this->generalSettingsTab = new GeneralSettingsTab(this);
    this->tabWidget->addTab(generalSettingsTab, tr("General"));
}


void SettingsDialog::showDialog()
{
    if (this->styleSettingsTab)
    {
        delete this->styleSettingsTab;
        this->styleSettingsTab = nullptr;
    }

    // Style Settings (has to be constructed new every time)
    this->styleSettingsTab = new StyleSettingsTab(this);
    this->tabWidget->addTab(this->styleSettingsTab, QIcon::fromTheme("color-select-symbolic"), tr("Style"));

    this->show();
}
