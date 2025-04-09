#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QObject>


class QTabWidget;
class QBoxLayout;
class QTextEdit;


class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    InfoDialog(QWidget* parent = nullptr);

    void printLicenseInfo();

    void showDialog();

private slots:
    void closed(int result);
    void currentTabChanged(int current);

private:
    QBoxLayout* layout = nullptr;
    QTabWidget* tabWidget = nullptr;

    QWidget* aboutTab = nullptr;
    QTextEdit* licenseTab = nullptr;
    QString licenseHTML = "";
};

#endif // INFODIALOG_H
