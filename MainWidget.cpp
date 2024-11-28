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
#include <cmath>

#if defined(Q_OS_WIN)
// Windows-specific code
#include <qt_windows.h>
#elif defined(Q_OS_MAC)
// macOS-specific code
#endif



MainWidget::MainWidget(QWidget *parent)
    : FramelessWidgetBase(parent)
{
    //this->setStyleSheet("QWidget{background-color:transparent;border:transparent;}");
    initUi();
    connectFun();
}

MainWidget::~MainWidget()
{
}

void MainWidget::initUi()
{
    QString styleWgt = R"(QWidget{background-color:transparent;border:1px;})";

    m_pCalTitleBar = new CalTitleBar(this);

    QWidget *pCalculatorWgt = new QWidget(this);
    pCalculatorWgt->setStyleSheet(styleWgt);
    pCalculatorWgt->setMinimumSize(320, 468);
    QVBoxLayout *pCalculatorLyt = new QVBoxLayout(pCalculatorWgt);
    pCalculatorLyt->setContentsMargins(0, 0, 0, 0);



    QWidget *pHWgt = new QWidget(this);
    pHWgt->setStyleSheet(styleWgt);
    pHWgt->setFixedHeight(36);
    QHBoxLayout *pHLyt = new QHBoxLayout(pHWgt);
    pHLyt->setContentsMargins(0, 0 , 0, 0);

    m_pMenuBtn = new QPushButton(this);
    m_pMenuBtn->setFixedSize(40, 36);
    m_pMenuBtn->setStyleSheet("QPushButton{border-image: url(:/image/menuBtn.png);}");

    m_pTopBtn = new QPushButton(this);
    m_pTopBtn->setFixedSize(32, 32);

    m_pHistoryBtn = new QPushButton(this);
    m_pHistoryBtn->setFixedSize(32, 32);
    m_pHistoryBtn->setStyleSheet("QPushButton{border-image: url(:/image/historyBtn.png);}");

    QString styleLbl = R"(
        QLabel{background-color:transparent;
                    border:transparent;
                    font-size: 16px;
                    color: black;
                    padding: 5px;}
    )";

    m_pTitileLbl = new QLabel(this);
    m_pTitileLbl->setStyleSheet(styleLbl);
    m_pTitileLbl->setText("标准");
    m_pTitileLbl->setFixedSize(60, 27);

    pHLyt->addWidget(m_pMenuBtn);
    pHLyt->addWidget(m_pTitileLbl);
    pHLyt->addWidget(m_pTopBtn);
    pHLyt->addStretch();
    pHLyt->addWidget(m_pHistoryBtn);
    pCalculatorLyt->addWidget(pHWgt);

    m_pNumShowLbl = new QLabel(this);
    m_pNumShowLbl->setMinimumSize(320, 75);
    m_pNumShowLbl->setStyleSheet("QLabel{background-color:#F3F3F3;"
                                 "border-left: 1px solid #6E6E6E;"
                                 "border-right: 1px solid #6E6E6E;"
                                 "border-top: 0px solid #6E6E6E;"
                                 "border-bottom: 0px solid #6E6E6E;"
                                 "font: 36pt;"
                                 "color: blank;"
                                 "}");
    pCalculatorLyt->addWidget(m_pNumShowLbl);

    QWidget *pMBtnwgt = new QWidget(this);
    pMBtnwgt->setStyleSheet(styleWgt);
    pMBtnwgt->setMinimumHeight(28);
    pMBtnwgt->setMaximumHeight(69);
    QHBoxLayout *pMhLyt = new QHBoxLayout(pMBtnwgt);
    pMhLyt->setContentsMargins(0, 0 , 0, 0);

    QString styleMBtn = R"(
        QPushButton{background-color:transparent;
                    border:transparent;
                    font-size: 16px;
                    color: black;
                    padding: 5px;}
    )";

    m_pMcBtn = new QPushButton(this);
    m_pMcBtn->setText("MC");
    m_pMcBtn->setMinimumSize(50, 28);
    m_pMcBtn->setMaximumSize(78, 69);
    m_pMcBtn->setStyleSheet(styleMBtn);

    m_pMrBtn = new QPushButton(this);
    m_pMrBtn->setText("MR");
    m_pMrBtn->setMinimumSize(50, 28);
    m_pMrBtn->setMaximumSize(78, 69);
    m_pMrBtn->setStyleSheet(styleMBtn);

    m_pMaddBtn = new QPushButton(this);
    m_pMaddBtn->setText("M+");
    m_pMaddBtn->setMinimumSize(50, 28);
    m_pMaddBtn->setMaximumSize(78, 69);
    m_pMaddBtn->setStyleSheet(styleMBtn);

    m_pMsubBtn = new QPushButton(this);
    m_pMsubBtn->setText("M-");
    m_pMsubBtn->setMinimumSize(50, 28);
    m_pMsubBtn->setMaximumSize(78, 69);
    m_pMsubBtn->setStyleSheet(styleMBtn);

    m_pMsBtn = new QPushButton(this);
    m_pMsBtn->setText("MS");
    m_pMsBtn->setMinimumSize(50, 28);
    m_pMsBtn->setMaximumSize(78, 69);
    m_pMsBtn->setStyleSheet(styleMBtn);

    m_pMBtn = new QPushButton(this);
    m_pMBtn->setText("M");
    m_pMBtn->setMinimumSize(50, 28);
    m_pMBtn->setMaximumSize(78, 69);
    m_pMBtn->setStyleSheet(styleMBtn);

    pMhLyt->addWidget(m_pMcBtn);
    pMhLyt->addWidget(m_pMrBtn);
    pMhLyt->addWidget(m_pMaddBtn);
    pMhLyt->addWidget(m_pMsubBtn);
    pMhLyt->addWidget(m_pMsBtn);
    pMhLyt->addWidget(m_pMBtn);
    pMhLyt->addStretch();
    pCalculatorLyt->addWidget(pMBtnwgt);

    QString style = R"(
        QPushButton{background-color:#FFFFFF;
                    border: 1px solid #AAAAAA;
                    border-radius: 5px;
                    font-size: 20px;
                    color: black;
                    padding: 5px;}
        QPushButton:hover{background-color:#FFFFFF;}
        QPushButton:pressed{background-color:#F6F6F6;border-color: #555;color: #AAA;}
        QPushButton:disabled{color: #333333;}
    )";

    // 键盘按钮布局
    QWidget *pKeyBoardWgt = new QWidget(this);
    pKeyBoardWgt->setMinimumSize(309, 287);
    pKeyBoardWgt->setStyleSheet(styleWgt);
    QGridLayout *pKeyBoarLyt = new QGridLayout(pKeyBoardWgt);
    pKeyBoarLyt->setContentsMargins(5, 5 , 5, 5);
    QStringList buttons = {
        "%", "CE","C", "←",
        "1/x", "x²", "²√x","/",
        "7", "8", "9", "*",
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "+/-", "0", ".", "="
    };

    int row = 0, col = 0;
    for (const QString &text : buttons)
    {
        QPushButton *button = new QPushButton(text, this);
        button->setStyleSheet(style);
        button->setMinimumSize(76, 47);
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

    pCalculatorLyt->addWidget(pKeyBoardWgt);

    // 窗口阴影
    QWidget *pShadowWidget = new QWidget(this);
    pShadowWidget->setMinimumSize(320, 500);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 0);
    effect->setColor(QColor(68, 68, 68));
    effect->setBlurRadius(5);
    pShadowWidget->setGraphicsEffect(effect);
    pShadowWidget->setStyleSheet("QWidget{background-color: #F3F3F3;border:1px solid #6E6E6E;}");

    QVBoxLayout *pShadowLyt = new QVBoxLayout(pShadowWidget);
    pShadowLyt->setContentsMargins(0, 0, 0, 0);
    pShadowLyt->addWidget(m_pCalTitleBar);
    pShadowLyt->addWidget(pCalculatorWgt);

    QVBoxLayout *pVLyt = new QVBoxLayout(this);
    pVLyt->setContentsMargins(2, 2, 2, 2);
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

void MainWidget::calculateDivisorX()
{
    bool ok;
    double value = m_pNumShowLbl->text().toDouble(&ok);
    if (ok && value >= 0)
    {
        double result = 1/value;
        currentInput = QString::number(result);
        updateDisplay();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid expression.");
    }
}

void MainWidget::calculatePercentage()
{
    bool ok;
    double value = m_pNumShowLbl->text().toDouble(&ok);
    if (ok && value >= 0)
    {
        double result = value/100;
        currentInput = QString::number(result);
        updateDisplay();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid expression.");
    }
}

void MainWidget::calculatePower()
{
    bool ok;
    double value = m_pNumShowLbl->text().toDouble(&ok);
    if (ok && value >= 0)
    {
        double result = pow(value, 2);
        currentInput = QString::number(result);
        updateDisplay();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid expression.");
    }
}

void MainWidget::calculateSquareRoot()
{
    bool ok;
    double value = m_pNumShowLbl->text().toDouble(&ok);
    if (ok && value >= 0)
    {
        double result = sqrt(value);
        currentInput = QString::number(result);
        updateDisplay();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid expression.");
    }
}

void MainWidget::onButtonClick()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString strtextBtn = button->text();
    QString strNum = m_pNumShowLbl->text();

    if (strtextBtn == "=") {
        calculateResult();
    }
    else if (strtextBtn == "%")
    {
        calculatePercentage();
    }
    else if (strtextBtn == "C" || strtextBtn == "CE")
    {
        currentInput.clear();
        m_pNumShowLbl->clear();
    }
    else if (strtextBtn == "←")
    {
        if (!strNum.isEmpty())
        {
            strNum.chop(1);// 去掉最后一个字符
            currentInput = strNum;
            updateDisplay();
        }
    }
    else if (strtextBtn == "1/x")
    {
        calculateDivisorX();
    }
    else if (strtextBtn == "x²")
    {
        calculatePower();
    }
    else if (strtextBtn == "²√x")
    {
        calculateSquareRoot();
    }
    else if (strtextBtn == "+/-")
    {
        if (!strNum.isEmpty())
        {
            if (strNum.startsWith("-"))
            {
                strNum.remove(0, 1); // 去掉负号
            }
            else
            {
                strNum.prepend("-"); // 添加负号
            }
            currentInput = strNum;
            updateDisplay();
        }
    }
    else
    {
        currentInput.append(strtextBtn);
        updateDisplay();
    }

}

