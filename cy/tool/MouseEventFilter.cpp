#include "MouseEventFilter.h"

#include <QMouseEvent>

namespace chongying {

bool MouseEventFilter::eventFilter(QObject *watched, QEvent *event) {
  Q_UNUSED(watched)
  if (event->type() == QMouseEvent::MouseButtonRelease) {
    QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
    if (mouse->button() == Qt::MiddleButton)
      emit this->middleClicked(mouse->pos());
  }
  return false;
}

}  // namespace chongying
