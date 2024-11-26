#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "FrameLessWidgetBase.h"

class CalTitleBar;
class QPushButton;
class QLabel;

class MainWidget : public FrameLessWidgetBase
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    void initUi();
    void connectFun();

private:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    CalTitleBar *m_pCalTitleBar;

    QPushButton *m_pMenuBtn;
    QPushButton *m_pTopBtn;
    QPushButton *m_pHistoryBtn;

    QPushButton *m_pMcBtn;
    QPushButton *m_pMrBtn;
    QPushButton *m_pMaddBtn;
    QPushButton *m_pMsubBtn;
    QPushButton *m_pMsBtn;
    QPushButton *m_pMBtn;

    QLabel *m_pTitileLbl;
    QLabel *m_pNumShowLbl;


};
#endif // MAINWIDGET_H
