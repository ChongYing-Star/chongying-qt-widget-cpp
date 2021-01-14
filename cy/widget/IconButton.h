#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>

#include "../IntString.h"

namespace chongying {

/**
 * @brief 图标按钮
 */
class IconButton : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(QString iconNormal READ icon_normal WRITE setIcon_normal)
  Q_PROPERTY(QString iconDisabled READ icon_disabled WRITE setIcon_disabled)
  QString m_iconNormal;
  QString m_iconDisabled;

  void __init__(const QString &type);

 public:
  /** @brief 图标按钮默认支持的类型 */
  enum Types {
    Add,
    Remove,
    Edit,
    Check,
    Search,
    Refresh,
    Query,
  };
  static const IntString TypeStrings;

  /**
   * @brief 支持自定义的实例化
   * type即为class名 您可以使用自己的class名 并在qss中支持它
   * @param type 类名
   * @param parent 父对象
   */
  explicit IconButton(const QString &type, QWidget *parent = nullptr);
  explicit IconButton(const Types &type, QWidget *parent = nullptr);

  QString icon_normal() const;
  void setIcon_normal(const QString &value);

  QString icon_disabled() const;
  void setIcon_disabled(const QString &value);

 signals:
};

}  // namespace chongying

#endif  // ICONBUTTON_H
