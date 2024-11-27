#ifndef FRAMELESSWIDGETBASE_H
#define FRAMELESSWIDGETBASE_H

#include <QWidget>
#include "ShadowWidget.h"

class FramelessWidgetBase : public ShadowWidget
{
    Q_OBJECT
public:
    explicit FramelessWidgetBase(QWidget *parent = nullptr);
    ~FramelessWidgetBase();

signals:

private:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:
    int m_nBorderWidget = 5;
};

#endif // FRAMELESSWIDGETBASE_H
