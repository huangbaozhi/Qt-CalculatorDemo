#include "MenuWidget.h"

#include <QToolButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QProgressBar>
#include <QScrollBar>
#include <QMessageBox>

MenuWidget::MenuWidget(QWidget *parent) : FramelessWidgetBase(parent)
{
    initUi();
}

void MenuWidget::initUi()
{
    setWindowTitle("Button List with Scroll and Progress Bar");
    setFixedSize(300, 400);

    // 创建垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_pBackBtn = new QPushButton(this);
    m_pBackBtn->setText("返回");
    m_pBackBtn->setFixedSize(40, 36);
    layout->addWidget(m_pBackBtn);

    // 创建一个QScrollArea，用于存放按钮列表
    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *buttonContainer = new QWidget(scrollArea);
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonContainer);

    // 创建按钮列表并将按钮添加到按钮容器中
    for (int i = 1; i <= 20; ++i) {
        QPushButton *button = new QPushButton(QString("按钮 %1").arg(i), this);
        buttonLayout->addWidget(button);
        connect(button, &QPushButton::clicked, this, [this, i]() {
            QMessageBox::information(this, QString("按钮 %1").arg(i), QString("你点击了按钮 %1").arg(i));
        });
    }

    buttonContainer->setLayout(buttonLayout);
    scrollArea->setWidget(buttonContainer);
    layout->addWidget(scrollArea);

    m_pSetBtn = new QPushButton(this);
    m_pSetBtn->setText("设置");
    m_pSetBtn->setFixedSize(40, 36);
    layout->addWidget(m_pSetBtn);

    // 连接滚动条的信号，更新进度条
    connect(scrollArea->verticalScrollBar(), &QScrollBar::valueChanged, this, [scrollArea ](int value) {
        int maxValue = scrollArea->verticalScrollBar()->maximum() - scrollArea->verticalScrollBar()->minimum();
    });
}

void MenuWidget::connectFun()
{

}
