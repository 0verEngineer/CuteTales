#ifndef STYLESETTINGSTAB_H
#define STYLESETTINGSTAB_H

#include <QObject>
#include <QWidget>
#include "qgridlayout.h"
#include "QCheckBox"


class QComboBox;


class StyleSettingsTab : public QWidget
{
    Q_OBJECT

public:
    explicit StyleSettingsTab(QWidget* parent = nullptr);
    ~StyleSettingsTab();

public slots:
    void styleSheetSelectorChanged(int index);
    void iconThemeSelectorChanged(int index);
    void useIconThemeCheckboxChanged(bool checked);

private:

    QGridLayout* layout = new QGridLayout(this);

    QComboBox* styleSheetSelector = nullptr;
    QComboBox* iconThemeSelector = nullptr;
    QComboBox* fileViewModeSelector = nullptr;
    QCheckBox* useIconThemeCB = nullptr;

private:
    void resetIconSelector(QString styleSheet);
};

#endif // STYLESETTINGSTAB_H
