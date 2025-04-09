
#include "MainWidget.h"

#include "qboxlayout.h"

MainWidget::MainWidget(QWidget* parent) {
    if (parent)
        setParent(parent);

    layout = new QBoxLayout(QBoxLayout::TopToBottom, nullptr);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    testLineEdit->setMaxLength(1000);
    testLabel->setText("testLabel text");
    auto testInnerLayout = new QBoxLayout(QBoxLayout::LeftToRight, nullptr);
    testInnerLayout->addWidget(testLabel);
    testInnerLayout->addWidget(testLineEdit);
    layout->addLayout(testInnerLayout);
}
