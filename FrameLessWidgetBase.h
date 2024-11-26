#ifndef FRAMELESSWIDGETBASE_H
#define FRAMELESSWIDGETBASE_H

#include <QWidget>

class FrameLessWidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit FrameLessWidgetBase(QWidget *parent = nullptr);
    ~FrameLessWidgetBase();

signals:

private:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private:
    int m_nBorderWidget = 5;
};

#endif // FRAMELESSWIDGETBASE_H
