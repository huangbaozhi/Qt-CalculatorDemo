#include "FrameLessWidgetBase.h"
#include <qt_windows.h>
#include <windows.h>
#include <windowsx.h>

FrameLessWidgetBase::FrameLessWidgetBase(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    setAttribute(Qt::WA_Hover);
}

FrameLessWidgetBase::~FrameLessWidgetBase()
{

}

bool FrameLessWidgetBase::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *param = static_cast<MSG*>(message);
    switch (param->message)
    {
    case WM_NCHITTEST:
    {
        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

        if (nX > m_nBorderWidget && nX < this->width() - m_nBorderWidget &&
                nY > m_nBorderWidget && nY < this->height() - m_nBorderWidget)
        {
            if (childAt(nX, nY) != nullptr)
                return QWidget::nativeEvent(eventType, message, result);
        }

        if ((nX > 0) && (nX < m_nBorderWidget))
            *result = HTLEFT;

        if ((nX > this->width() - m_nBorderWidget) && (nX < this->width()))
            *result = HTRIGHT;

        if ((nY > 0) && (nY < m_nBorderWidget))
            *result = HTTOP;

        if ((nY > this->height() - m_nBorderWidget) && (nY < this->height()))
            *result = HTBOTTOM;

        if ((nX > 0) && (nX < m_nBorderWidget) && (nY > 0) && (nY < m_nBorderWidget))
            *result = HTTOPLEFT;

        if ((nX > this->width() - m_nBorderWidget) && (nX < this->width())
                && (nY > 0) && (nY < m_nBorderWidget))
            *result = HTTOPRIGHT;

        if ((nX > 0) && (nX < m_nBorderWidget)
                && (nY > this->height() - m_nBorderWidget) && (nY < this->height()))
            *result = HTBOTTOMLEFT;

        if ((nX > this->width() - m_nBorderWidget) && (nX < this->width())
                && (nY > this->height() - m_nBorderWidget) && (nY < this->height()))
            *result = HTBOTTOMRIGHT;

        return true;
    }
    }
    return false;
}




