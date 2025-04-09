#include "InfoDialog.h"

#include "qscrollbar.h"
#include "qboxlayout.h"
#include "qtabwidget.h"
#include "qtextedit.h"
#include "qfile.h"

// Todo needed?
//#ifdef Q_OS_WIN
//#include "../windows/titleBar.h"
//#endif


InfoDialog::InfoDialog(QWidget* parent)
{
    if (parent)
        this->setParent(parent);

#ifdef Q_OS_WIN
    setDarkTitleBarWindows(reinterpret_cast<HWND>(this->winId()));
#endif

    this->setMinimumSize(600, 420);

    this->layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
    this->setWindowTitle(tr("Info"));

    this->tabWidget = new QTabWidget(this);
    this->layout->addWidget(this->tabWidget);

    this->aboutTab = new QWidget(this);
    this->tabWidget->addTab(this->aboutTab, QIcon::fromTheme("help-about-symbolic"), tr("About"));

    this->licenseTab = new QTextEdit(this);
    this->tabWidget->addTab(this->licenseTab, QIcon::fromTheme("emblem-favorite-symbolic"), tr("Licenses"));
    printLicenseInfo();

    connect(tabWidget, &QTabWidget::currentChanged, this, &InfoDialog::currentTabChanged);
    connect(this, &InfoDialog::finished, this, &InfoDialog::closed);
}


void InfoDialog::printLicenseInfo()
{
    this->licenseTab->setReadOnly(true);

    if (this->licenseHTML.length() < 1)
    {
        // Todo now: licenses file is not opening
        QFile licensesHtmlFile = QFile(":/licenses.html");
        if (licensesHtmlFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&licensesHtmlFile);
            this->licenseHTML = in.readAll();
        }
    }

    this->licenseTab->insertHtml(licenseHTML);
}


void InfoDialog::showDialog()
{
    this->show();
}


void InfoDialog::closed(int result)
{
    disconnect(tabWidget, &QTabWidget::currentChanged, this, &InfoDialog::currentTabChanged);
    disconnect(this, &InfoDialog::finished, this, &InfoDialog::closed);
}


void InfoDialog::currentTabChanged(int current)
{
    if(current == 1) // License tab
    {
        // QTextEdit is auto-scrolling to the bottom if text is added
        this->licenseTab->verticalScrollBar()->setValue(this->licenseTab->verticalScrollBar()->minimum());
    }
}

