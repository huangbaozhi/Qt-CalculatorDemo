#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "FramelessWidgetBase.h"
#include <QFrame>
#include <QTimer>

class CalTitleBar;
class QPushButton;
class QLabel;
class MenuWidget;

class MainWidget : public FramelessWidgetBase
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

    void updateDisplay();

    void calculateResult();
    void calculateDivisorX();
    void calculatePercentage();
    void calculatePower();
    void calculateSquareRoot();

private slots:
    void onButtonClick();
    void startSlideAnimation();
    void onMenuClick();
    void onTimeOut();



private:
    CalTitleBar *m_pCalTitleBar;
    MenuWidget  *m_pMenuWidget;
    QWidget *newWindow;
    QWidget *pShadowWidget;

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

    QFrame *m_pSlideWidget;  // 用于滑动的窗口
    QAction *m_pSlideAction;

    QString currentInput;
    double result;              // 计算结果
    QString currentOperator;    // 当前操作符

    int targetWidth;
    int step;
    QTimer *timer;


};
#endif // MAINWIDGET_H
