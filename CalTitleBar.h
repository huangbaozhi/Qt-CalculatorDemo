#ifndef CALTITLEBAR_H
#define CALTITLEBAR_H

#include <QWidget>

class QPushButton;
class QLabel;

class CalTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CalTitleBar(QWidget *parent = nullptr);

signals:
    void signClose();

private:
    void initUi();
    void connectFun();

private slots:
    void slotClicked();

private:
    QLabel *m_pLogoLbl;
    QLabel *m_pTitleLbl;

    QPushButton *m_pMinBtn;
    QPushButton *m_pMaxBtn;
    QPushButton *m_pCloseBtn;
};

#endif // CALTITLEBAR_H
