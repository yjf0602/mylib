#include "FFramelessWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

FFramelessWindow::FFramelessWindow(QWidget *parent) :
    QWidget(parent),
    mIsMove(false),
    mIsHResize(false),
    mIsVResize(false),
    mIsDResize(false)
{
    mBackGroundWidget = new QWidget();
    QGridLayout *glayout = new QGridLayout();
    glayout->setContentsMargins(5,5,5,5);
    glayout->addWidget(mBackGroundWidget);
    this->setLayout(glayout);

    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    mBackGroundWidget->setStyleSheet("background-color: rgb(250, 250, 250);");

    QGraphicsDropShadowEffect *Shadow = new QGraphicsDropShadowEffect();
    Shadow->setBlurRadius(8.0);
    Shadow->setColor(QColor(63, 63, 63, 180));
    Shadow->setOffset(0, 0);
    mBackGroundWidget->setGraphicsEffect(Shadow);

    mMainWidget = new QWidget();
    mResizeWidgetRight = new QWidget();
    mResizeWidgetRight->setFixedWidth(5);
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->setContentsMargins(0,0,0,0);
    hLayout1->setSpacing(0);
    hLayout1->addWidget(mMainWidget);
    hLayout1->addWidget(mResizeWidgetRight);

    mResizeWidgetBottom = new QWidget();
    mResizeWidgetBottom->setFixedHeight(5);
    mResizeWidgetBottom->setMinimumHeight(5);
    mResizeWidgetRightBottom = new QWidget();
    mResizeWidgetRightBottom->setFixedSize(5, 5);
    mResizeWidgetRightBottom->setMinimumHeight(5);
    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->setContentsMargins(0,0,0,0);
    hLayout2->setSpacing(0);

    hLayout2->addWidget(mResizeWidgetBottom);
    hLayout2->addWidget(mResizeWidgetRightBottom);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(5,5,0,0);
    vLayout->setSpacing(0);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);

    mBackGroundWidget->setLayout(vLayout);

    mResizeWidgetRight->setMouseTracking(true);
    mResizeWidgetRight->setCursor(Qt::SizeHorCursor);

    mResizeWidgetBottom->setMouseTracking(true);
    mResizeWidgetBottom->setCursor(Qt::SizeVerCursor);

    mResizeWidgetRightBottom->setMouseTracking(true);
    mResizeWidgetRightBottom->setCursor(Qt::SizeFDiagCursor);

    mMainLayout = new QGridLayout();
    mMainLayout->setMargin(0);
    mMainLayout->setSpacing(0);
    mMainWidget->setLayout(mMainLayout);
}

void FFramelessWindow::setContentWidget(QWidget *w)
{
    mMainLayout->addWidget(w);
}

void FFramelessWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint hp = mResizeWidgetRight->mapToGlobal(QPoint(0,0));
        QRect hr = QRect(hp, mResizeWidgetRight->size());

        QPoint vp = mResizeWidgetBottom->mapToGlobal(QPoint(0,0));
        QRect vr = QRect(vp, mResizeWidgetBottom->size());

        QPoint dp = mResizeWidgetRightBottom->mapToGlobal(QPoint(0,0));
        QRect dr = QRect(dp, mResizeWidgetRightBottom->size());

        if(hr.contains(event->globalPos()))
        {
            mIsHResize = true;
        }
        else if(vr.contains(event->globalPos()))
        {
            mIsVResize = true;
        }
        else if(dr.contains(event->globalPos()))
        {
            mIsDResize = true;
        }
        else
        {
            mIsMove = true;
        }
        mLastPos = event->globalPos();
        mLastSize = this->size();
    }
}

void FFramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mIsMove)
    {
        this->move(this->pos() + event->globalPos() - mLastPos);
        mLastPos = event->globalPos();
    }
    else if(mIsHResize)
    {
        this->resize(mLastSize.width() + event->globalPos().x() - mLastPos.x(), mLastSize.height());
    }
    else if(mIsVResize)
    {
        this->resize(mLastSize.width(), mLastSize.height() + event->globalPos().y() - mLastPos.y());
    }
    else if(mIsDResize)
    {
       this->resize(mLastSize.width() + event->globalPos().x() - mLastPos.x(),
                    mLastSize.height() + event->globalPos().y() - mLastPos.y());
    }
}

void FFramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    mIsMove = false;
    mIsDResize = false;
    mIsHResize = false;
    mIsVResize = false;
}
