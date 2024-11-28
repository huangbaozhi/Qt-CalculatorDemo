#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "FramelessWidgetBase.h"

class CalTitleBar;
class QPushButton;
class QLabel;

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
    void calculatePercentage();
    void calculatePower();
    void calculateSquareRoot();

private slots:
    void onButtonClick();



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

    QString currentInput;
    double result;              // 计算结果
    QString currentOperator;    // 当前操作符


};
#endif // MAINWIDGET_H
