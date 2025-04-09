#include <QLabel>
#include <QGridLayout>
#include <QComboBox>
#include "GeneralSettingsTab.h"
#include "app/ApplicationManager.h"


GeneralSettingsTab::GeneralSettingsTab(QWidget *parent)
    : QWidget{parent}
{
    if (parent)
        this->setParent(parent);

    auto settings = ApplicationManager::getInstance()->getSettings();
    auto gridLayout = new QGridLayout(this);
    this->setLayout(gridLayout);

    // ComboBox order (index) identical to WORKSPACE_RESTORE_MODE enum
    auto* restoreWorkspaceModeComboBox = new QComboBox(this);
    restoreWorkspaceModeComboBox->addItem(tr("Always"));
    restoreWorkspaceModeComboBox->addItem(tr("Never"));
    restoreWorkspaceModeComboBox->addItem(tr("Ask on close"));
    //restoreWorkspaceModeComboBox->setCurrentIndex(settings->general.workspaceRestoreMode);

    gridLayout->addWidget(new QLabel(tr("Restore workspace on Application restart")), 0, 0);
    gridLayout->addWidget(restoreWorkspaceModeComboBox, 0, 1);

    /*
    connect(restoreWorkspaceModeComboBox, &QComboBox::currentIndexChanged, this, [=](int index){
       settings->general.workspaceRestoreMode = static_cast<WORKSPACE_RESTORE_MODE>(index);
    });*/
}
