#include "MoveHandle.h"

#include <QMap>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QVariant>

namespace chongying {

static const QMap<Qt::Orientation, QString> ClassName{
    {Qt::Horizontal, QStringLiteral("Horizontal")},
    {Qt::Vertical, QStringLiteral("Vertical")},
};

void MoveHandle::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool MoveHandle::eventFilter(QObject *obj, QEvent *event) {
  if (obj != this) return false;
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
    if (e->button() == Qt::LeftButton) {
      if (this->orientation_ == Qt::Vertical)
        this->mousePos_ = e->y();
      else
        this->mousePos_ = e->x();
    }
  }
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *e = static_cast<QMouseEvent *>(event);
    if ((e->buttons() & Qt::LeftButton) && (this->mousePos_ > 0)) {
      int cha = 0;
      if (this->orientation_ == Qt::Vertical)
        cha = e->y() - this->mousePos_;
      else
        cha = e->x() - this->mousePos_;
      emit moved(cha);
    }
  }
  if (event->type() == QEvent::MouseButtonRelease) {
    this->mousePos_ = -1;
  }
  return false;
}

MoveHandle::MoveHandle(const Qt::Orientation &orientation, QWidget *parent)
    : QWidget(parent), orientation_(orientation), mousePos_(-1) {
  this->setProperty("class", ClassName[orientation]);
  if (orientation == Qt::Vertical) {
    this->setCursor(Qt::SplitVCursor);
  } else {
    this->setCursor(Qt::SplitHCursor);
  }
  this->installEventFilter(this);
}

}  // namespace chongying
