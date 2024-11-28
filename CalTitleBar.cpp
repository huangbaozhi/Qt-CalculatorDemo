#include "CalTitleBar.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

CalTitleBar::CalTitleBar(QWidget *parent) : QWidget(parent)
{

    this->setStyleSheet("QWidget{background-color:transparent;border:transparent;}");
    initUi();
    connectFun();
}

void CalTitleBar::initUi()
{
    setAttribute(Qt::WA_StyledBackground);
    this->setFixedHeight(32 + 5 * 2);
    this->setMinimumSize(320, 32);

    m_pLogoLbl = new QLabel(this);
    m_pLogoLbl->setFixedSize(32, 32);
    m_pLogoLbl->setStyleSheet("QLabel{border-image: url(:/image/logo_32px.png);}");

    QString styleLbl = R"(
        QLabel{background-color:transparent;
                    border:transparent;
                    font-size: 16px;
                    color: black;
                    padding: 5px;}
    )";

    m_pTitleLbl = new QLabel(this);
    m_pTitleLbl->setFixedSize(100, 32);
    m_pTitleLbl->setText("计算器");
    m_pTitleLbl->setStyleSheet(styleLbl);

    m_pMinBtn = new QPushButton(this);
    m_pMinBtn->setFixedSize(32, 32);
    m_pMinBtn->setStyleSheet("QPushButton{border-image: url(:/image/minBtn.png);}");

    m_pMaxBtn = new QPushButton(this);
    m_pMaxBtn->setFixedSize(32, 32);
    m_pMaxBtn->setStyleSheet("QPushButton{border-image: url(:/image/maxBtn.png);}");

    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(32, 32);
    m_pCloseBtn->setStyleSheet("QPushButton{border-image: url(:/image/closeBtn.png);}");

    QHBoxLayout *pHTitleLyt = new QHBoxLayout(this);
    pHTitleLyt->setContentsMargins(0, 0, 0, 0);
    pHTitleLyt->addWidget(m_pLogoLbl);
    pHTitleLyt->addWidget(m_pTitleLbl);
    pHTitleLyt->addStretch();
    pHTitleLyt->addWidget(m_pMinBtn);
    pHTitleLyt->addWidget(m_pMaxBtn);
    pHTitleLyt->addWidget(m_pCloseBtn);
}

void CalTitleBar::connectFun()
{
    connect(m_pMinBtn, &QPushButton::clicked, this, &CalTitleBar::slotClicked);
    connect(m_pMaxBtn, &QPushButton::clicked, this, &CalTitleBar::slotClicked);
    connect(m_pCloseBtn, &QPushButton::clicked, this, &CalTitleBar::slotClicked);
}

void CalTitleBar::slotClicked()
{
    QPushButton *pBtn = qobject_cast<QPushButton*>(sender());

    QWidget *pWndWgt = this->window();

    if (pBtn == m_pMinBtn)
    {
        pWndWgt->showMinimized();
    }
    else if (pBtn == m_pMaxBtn)
    {
        if (pWndWgt->isMaximized())
        {
            pWndWgt->showNormal();
            m_pMaxBtn->setStyleSheet("QPushButton{border-image: url(:/image/maxBtn.png);}");
        }
        else
        {
            pWndWgt->showMaximized();
            m_pMaxBtn->setStyleSheet("QPushButton{border-image: url(:/image/maxBnt_1.png);}");
        }
    }
    else if (pBtn == m_pCloseBtn)
    {
        emit signClose();
    }
}
