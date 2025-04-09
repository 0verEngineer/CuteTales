#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "StyleSettingsTab.h"
#include "GeneralSettingsTab.h"
#include <QDialog>
#include <QObject>


class QTabWidget;
class QBoxLayout;


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget* parent = nullptr);

    void showDialog();

private:
    QBoxLayout* layout = nullptr;
    QTabWidget* tabWidget = nullptr;

    GeneralSettingsTab* generalSettingsTab = nullptr;
    StyleSettingsTab* styleSettingsTab = nullptr;
};

#endif // SETTINGSDIALOG_H
