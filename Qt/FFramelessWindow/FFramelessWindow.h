#ifndef FFRAMELESSWINDOW_H
#define FFRAMELESSWINDOW_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QGridLayout>

class FFramelessWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FFramelessWindow(QWidget *parent = nullptr);
    void setContentWidget(QWidget *w);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool mIsMove;
    bool mIsHResize;
    bool mIsVResize;
    bool mIsDResize;
    QPoint mLastPos;
    QSize mLastSize;

    QWidget *mBackGroundWidget;
    QWidget *mMainWidget;
    QGridLayout *mMainLayout;
    QWidget *mResizeWidgetRight;
    QWidget *mResizeWidgetBottom;
    QWidget *mResizeWidgetRightBottom;
};

#endif // FFRAMELESSWINDOW_H
