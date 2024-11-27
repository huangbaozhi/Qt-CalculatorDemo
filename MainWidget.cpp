#include "MainWidget.h"
#include "CalTitleBar.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QRegExpValidator>
#include <QScriptEngine>
#include <QScriptValue>
#include <QMessageBox>

#include "Eigen/Dense"
using namespace  Eigen;

#if defined(Q_OS_WIN)
// Windows-specific code
#include <qt_windows.h>
#elif defined(Q_OS_MAC)
// macOS-specific code
#endif



MainWidget::MainWidget(QWidget *parent)
    : FramelessWidgetBase(parent)
{
    initUi();
    connectFun();
}

MainWidget::~MainWidget()
{
}

void MainWidget::initUi()
{
    m_pCalTitleBar = new CalTitleBar(this);

    QWidget *pCalculatorWgt = new QWidget(this);
    pCalculatorWgt->setMinimumSize(320, 468);
    QVBoxLayout *pCalculatorLyt = new QVBoxLayout(pCalculatorWgt);
    pCalculatorLyt->setContentsMargins(0, 0, 0, 0);

    QWidget *pHWgt = new QWidget(this);
    pHWgt->setFixedHeight(36);
    QHBoxLayout *pHLyt = new QHBoxLayout(pHWgt);
    pHLyt->setContentsMargins(0, 0 , 0, 0);

    m_pMenuBtn = new QPushButton(this);
    m_pMenuBtn->setFixedSize(40, 36);

    m_pTopBtn = new QPushButton(this);
    m_pTopBtn->setFixedSize(32, 32);

    m_pHistoryBtn = new QPushButton(this);
    m_pHistoryBtn->setFixedSize(32, 32);

    m_pTitileLbl = new QLabel(this);
    m_pTitileLbl->setText("标准");
    m_pTitileLbl->setFixedSize(40, 27);

    pHLyt->addWidget(m_pMenuBtn);
    pHLyt->addWidget(m_pTitileLbl);
    pHLyt->addWidget(m_pTopBtn);
    pHLyt->addStretch();
    pHLyt->addWidget(m_pHistoryBtn);
    pCalculatorLyt->addWidget(pHWgt);

    m_pNumShowLbl = new QLabel(this);
    m_pNumShowLbl->setMinimumSize(320, 75);
    m_pNumShowLbl->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    pCalculatorLyt->addWidget(m_pNumShowLbl);

    QWidget *pMBtnwgt = new QWidget(this);
    pMBtnwgt->setMinimumHeight(28);
    pMBtnwgt->setMaximumHeight(69);
    QHBoxLayout *pMhLyt = new QHBoxLayout(pMBtnwgt);
    pMhLyt->setContentsMargins(0, 0 , 0, 0);

    m_pMcBtn = new QPushButton(this);
    m_pMcBtn->setText("MC");
    m_pMcBtn->setMinimumSize(50, 28);
    m_pMcBtn->setMaximumSize(78, 69);

    m_pMrBtn = new QPushButton(this);
    m_pMrBtn->setText("MR");
    m_pMrBtn->setMinimumSize(50, 28);
    m_pMrBtn->setMaximumSize(78, 69);

    m_pMaddBtn = new QPushButton(this);
    m_pMaddBtn->setText("M+");
    m_pMaddBtn->setMinimumSize(50, 28);
    m_pMaddBtn->setMaximumSize(78, 69);

    m_pMsubBtn = new QPushButton(this);
    m_pMsubBtn->setText("M-");
    m_pMsubBtn->setMinimumSize(50, 28);
    m_pMsubBtn->setMaximumSize(78, 69);

    m_pMsBtn = new QPushButton(this);
    m_pMsBtn->setText("MS");
    m_pMsBtn->setMinimumSize(50, 28);
    m_pMsBtn->setMaximumSize(78, 69);

    m_pMBtn = new QPushButton(this);
    m_pMBtn->setText("M^");
    m_pMBtn->setMinimumSize(50, 28);
    m_pMBtn->setMaximumSize(78, 69);

    pMhLyt->addWidget(m_pMcBtn);
    pMhLyt->addWidget(m_pMrBtn);
    pMhLyt->addWidget(m_pMaddBtn);
    pMhLyt->addWidget(m_pMsubBtn);
    pMhLyt->addWidget(m_pMsBtn);
    pMhLyt->addWidget(m_pMBtn);
    pMhLyt->addStretch();
    pCalculatorLyt->addWidget(pMBtnwgt);

    // 键盘按钮布局
    QWidget *pKeyBoardWgt = new QWidget(this);
    QGridLayout *pKeyBoarLyt = new QGridLayout(pKeyBoardWgt);
    pKeyBoarLyt->setContentsMargins(5, 5 , 5, 5);
    QStringList buttons = {
        "%", "CE","C", "error",
        "1/x", "x^2", "(2√x)","/",
        "7", "8", "9", "*",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "+/-", "0", ".", "="
    };

    int row = 0, col = 0;
    for (const QString &text : buttons)
    {
        QPushButton *button = new QPushButton(text, this);
        button->setMinimumSize(77, 47);
        button->setMaximumSize(397, 111);
        pKeyBoarLyt->addWidget(button, row, col);
        connect(button, &QPushButton::clicked, this, &MainWidget::onButtonClick);
        col++;
        if (col > 3)
        {
            col = 0;
            row++;
        }
    }

//    // 清除按钮与等号按钮额外处理
//    QPushButton *clearButton = findChild<QPushButton*>("C");
//    connect(clearButton, &QPushButton::clicked, this, &MainWidget::onClearClick);
//    QPushButton *equalsButton = findChild<QPushButton*>("=");
//    connect(equalsButton, &QPushButton::clicked, this, &MainWidget::onEqualsClick);

    pCalculatorLyt->addWidget(pKeyBoardWgt);

    // 窗口阴影
    QWidget *pShadowWidget = new QWidget(this);
    pShadowWidget->setMinimumSize(320, 498);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 0);
    effect->setColor(QColor(68, 68, 68));
    effect->setBlurRadius(5);
    pShadowWidget->setGraphicsEffect(effect);
    pShadowWidget->setStyleSheet("QWidget{background-color: #F3F3F3;border:1px solid #6E6E6E}");

    QVBoxLayout *pShadowLyt = new QVBoxLayout(pShadowWidget);
    pShadowLyt->setContentsMargins(0, 0, 0, 0);
    pShadowLyt->addWidget(m_pCalTitleBar);
    pShadowLyt->addWidget(pCalculatorWgt);

    QVBoxLayout *pVLyt = new QVBoxLayout(this);
    pVLyt->setContentsMargins(1, 1, 1, 1);
    pVLyt->addWidget(pShadowWidget);
}

void MainWidget::connectFun()
{
    connect(m_pCalTitleBar, &CalTitleBar::signClose, this, &MainWidget::close);
}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if (ReleaseCapture())
    {
        QWidget *pWindowWgt = this->window();
        if (pWindowWgt->isTopLevel())
        {
#if defined(Q_OS_WIN)
            SendMessage(HWND(pWindowWgt->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
#elif defined(Q_OS_MAC)
#endif
        }
    }
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void MainWidget::updateDisplay()
{
    m_pNumShowLbl->setText(currentInput);
}

void MainWidget::calculateResult()
{
    try {
        // 使用QScriptEngine进行表达式计算
        QScriptEngine engine;
        QScriptValue result = engine.evaluate(currentInput);
        if (result.isNumber()) {
            currentInput = QString::number(result.toNumber());
            updateDisplay();
        } else {
            QMessageBox::critical(this, "Error", "Invalid expression.");
        }
    } catch (...) {
        QMessageBox::critical(this, "Error", "Invalid expression.");
    }
}

void MainWidget::onButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString text = button->text();

    if (text == "=") {
        calculateResult();
    }
    else
    {
        currentInput.append(text);
        updateDisplay();
    }

}
