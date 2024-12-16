#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include "FramelessWidgetBase.h"
#include <QWidget>

class QPushButton;

class MenuWidget : public FramelessWidgetBase
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

signals:

private:
    void initUi();
    void connectFun();

private:
    QPushButton *m_pBackBtn;
    QPushButton *m_pSetBtn;

};

#endif // MENUWIDGET_H
