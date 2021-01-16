#ifndef CHONGYING_TOOL_MOUSEEVENTFILTER_H
#define CHONGYING_TOOL_MOUSEEVENTFILTER_H

#include <QObject>

namespace chongying {

/**
 * @brief 鼠标事件过滤器
 */
class MouseEventFilter : public QObject {
  Q_OBJECT
 public:
  using QObject::QObject;
  bool eventFilter(QObject *watched, QEvent *event) override;

 signals:
  /**
   * @brief 当鼠标中键点击时 发出该信号
   * @param point
   */
  void middleClicked(const QPoint &point);
};

}  // namespace chongying

#endif  // CHONGYING_TOOL_MOUSEEVENTFILTER_H
