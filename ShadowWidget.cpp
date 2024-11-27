#include "ShadowWidget.h"

#include <QGraphicsDropShadowEffect>
#include <QVBoxLayout>

ShadowWidget::ShadowWidget(QWidget *parent) : QWidget(parent)
{
    //initUi();
}

void ShadowWidget::initUi()
{
    QVBoxLayout *pVLyt = new QVBoxLayout(this);
    pVLyt->setContentsMargins(0, 0, 0, 0);

    QWidget *m_pShadowWidget = new QWidget(this);
    m_pShadowWidget->setMinimumSize(320, 468);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 0);
    effect->setColor(QColor(68, 68, 68));
    effect->setBlurRadius(10);
    m_pShadowWidget->setGraphicsEffect(effect);
    m_pShadowWidget->setStyleSheet("QWidget{background-color: rgb(255, 254, 253);border-radius: 10px;}");

    pVLyt->addWidget(m_pShadowWidget);
    pVLyt->setContentsMargins(2, 2, 2, 2);
}
