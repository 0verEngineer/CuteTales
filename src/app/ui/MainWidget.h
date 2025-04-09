
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qwidget.h"
#include "qlabel.h"
#include "qlineedit.h"


class QBoxLayout;

class MainWidget : public QWidget {
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = nullptr);

private:
    QLineEdit* testLineEdit = new QLineEdit(this);

    QBoxLayout* layout;

    QLabel* testLabel = new QLabel(this);
};



#endif //MAINWIDGET_H
