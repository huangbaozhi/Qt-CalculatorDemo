#include "MainWidget.h"
#include "CalTitleBar.h"

#include <qt_windows.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

MainWidget::MainWidget(QWidget *parent)
    : FrameLessWidgetBase(parent)
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
    pCalculatorWgt->setStyleSheet("QWidget{background-color:rgb(54,54,54);}");
    QVBoxLayout *pCalculatorLyt = new QVBoxLayout(pCalculatorWgt);

    QWidget *pHWgt = new QWidget(this);
    QHBoxLayout *pHLyt = new QHBoxLayout(pHWgt);
    m_pMenuBtn = new QPushButton(this);
    m_pTopBtn = new QPushButton(this);
    m_pHistoryBtn = new QPushButton(this);
    m_pTitileLbl = new QLabel(this);
    m_pTitileLbl->setText("标准");
    pHLyt->addWidget(m_pMenuBtn);
    pHLyt->addWidget(m_pTitileLbl);
    pHLyt->addWidget(m_pTopBtn);
    pHLyt->addStretch();
    pHLyt->addWidget(m_pHistoryBtn);

    pCalculatorLyt->addWidget(pHWgt);

    m_pNumShowLbl = new QLabel(this);
    m_pNumShowLbl->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    pCalculatorLyt->addWidget(m_pNumShowLbl);

    QWidget *pMwgt = new QWidget(this);
    QHBoxLayout *pMhLyt = new QHBoxLayout(pMwgt);
    m_pMcBtn = new QPushButton(this);
    m_pMrBtn = new QPushButton(this);
    m_pMaddBtn = new QPushButton(this);
    m_pMsubBtn = new QPushButton(this);
    m_pMsBtn = new QPushButton(this);
    m_pMBtn = new QPushButton(this);
    pMhLyt->addWidget(m_pMcBtn);
    pMhLyt->addWidget(m_pMrBtn);
    pMhLyt->addWidget(m_pMaddBtn);
    pMhLyt->addWidget(m_pMsubBtn);
    pMhLyt->addWidget(m_pMsBtn);
    pMhLyt->addWidget(m_pMBtn);

    pCalculatorLyt->addWidget(pMwgt);

    QVBoxLayout *pVLyt = new QVBoxLayout(this);
    pVLyt->setContentsMargins(0, 0, 0, 0);
    pVLyt->addWidget(m_pCalTitleBar);
    pVLyt->addWidget(pCalculatorWgt);
    //pVLyt->addLayout(pHLyt);
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
            SendMessage(HWND(pWindowWgt->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
}

void MainWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

}

