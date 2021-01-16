#ifndef CHONGYING_VIEW_HEADERVIEW_H
#define CHONGYING_VIEW_HEADERVIEW_H

#include <QHeaderView>

namespace chongying {

/**
 * @brief 头部视图
 */
class HeaderView : public QHeaderView {
  Q_OBJECT
  void onSectionResized(const int &logicalIndex, const int &oldSize,
                        const int &newSize);
  void contextMenu(const QPoint &point);
  int sectionCount() const;

 public:
  explicit HeaderView(Qt::Orientation orientation = Qt::Horizontal,
                      QWidget *parent = nullptr);
  void setModel(QAbstractItemModel *model) override;

 public slots:
  /** @brief 用于自动调整大小 */
  void autoSize() noexcept;
  /** @brief 用于刷新视图 当模型发生变化时 应当被调用 */
  void refresh() noexcept;

 signals:
};

}  // namespace chongying

#endif  // CHONGYING_VIEW_HEADERVIEW_H
