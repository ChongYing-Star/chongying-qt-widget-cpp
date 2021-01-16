#ifndef CHONGYING_DISPLAYSTRING_H
#define CHONGYING_DISPLAYSTRING_H

#include <QObject>

#include "Global.h"
#include "IntString.h"

namespace chongying {

/**
 * @brief 显示字符串类 用于获取翻译后的字符串
 */
class DisplayString : public QObject {
  Q_OBJECT
 public:
  /** @brief 按钮 */
  enum Buttons { Ok, No, Yes, Cancel, Refresh };
  static const IntString ButtonStrings;

 public:
  /** @brief 主机名 */
  static const QString HostName;

  /** @brief 暂时没有什么用处 无需实例化 */
  explicit DisplayString(QObject *parent = nullptr);

  /**
   * @brief 按钮翻译
   * @param button 按钮
   * @return 翻译后的字符串
   */
  static QString ButtonText(const Buttons &button,
                            const QString &default_ = QString()) noexcept;
  /**
   * @brief 按钮翻译
   * @param button 按钮字符串
   * @return 翻译后的字符串
   */
  static QString ButtonText(const QString &button) noexcept;

 signals:
};

}  // namespace chongying

#endif  // CHONGYING_DISPLAYSTRING_H
