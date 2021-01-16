#ifndef CHONGYING_WIDGET_MOVEHANDLE_H
#define CHONGYING_WIDGET_MOVEHANDLE_H

#include <QWidget>

namespace chongying {

/**
 * @brief 移动手柄
 * 常用于改变相关部件大小
 */
class MoveHandle : public QWidget {
  Q_OBJECT
  Qt::Orientation orientation_;
  qint32 mousePos_;

 protected:
  void paintEvent(QPaintEvent *event) override;
  bool eventFilter(QObject *obj, QEvent *event) override;

 public:
  explicit MoveHandle(const Qt::Orientation &orientation,
                      QWidget *parent = nullptr);

 signals:
  /**
   * @brief 当被鼠标拖动时 发出该信号
   * @param distance 距离
   */
  void moved(const int &distance) const;
};

}  // namespace chongying

#endif  // CHONGYING_WIDGET_MOVEHANDLE_H
