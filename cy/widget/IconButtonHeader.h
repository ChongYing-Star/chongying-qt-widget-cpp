#ifndef CHONGYING_WIDGET_ICONBUTTONHEADER_H
#define CHONGYING_WIDGET_ICONBUTTONHEADER_H

#include <QWidget>

#include "IconButton.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QBoxLayout;
QT_END_NAMESPACE

namespace chongying {

/**
 * @brief 图标按钮头部
 */
class IconButtonHeader : public QWidget {
  Q_OBJECT

  QLabel *label;
  QBoxLayout *layout;
  QList<IconButton *> buttons;

 protected:
  void paintEvent(QPaintEvent *event) override;

 public:
  explicit IconButtonHeader(QWidget *parent = nullptr);
  /** @brief 设置头部文本 */
  void setText(const QString &text);
  QString text() const;
  /** @brief 添加按钮 */
  IconButton *addButton(const IconButton::Types &type,
                        const QString &tooltip = QString());
  /** @brief 添加按钮 */
  IconButton *addButton(const QString &type,
                        const QString &tooltip = QString());

 signals:
};

}  // namespace chongying

#endif  // CHONGYING_WIDGET_ICONBUTTONHEADER_H
