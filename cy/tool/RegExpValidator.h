#ifndef CHONGYING_TOOL_STRINGVALIDATOR_H
#define CHONGYING_TOOL_STRINGVALIDATOR_H

#include <QRegExpValidator>

namespace chongying {

/**
 * @brief 字符串正则验证纠错器
 */
class RegExpValidator : public QRegExpValidator {
  Q_OBJECT
  /** @brief 需要被处理的正则 */
  const QRegExp regexp_reject_;
  /** @brief 替换的目标字符串 */
  const QString replace_string_;

 public:
  /**
   * @brief 构造函数
   * @param regexp 正确通过的正则
   * @param r_regexp 需要被处理的正则
   * @param replace 替换的目标字符串
   * @param parent 父对象
   */
  explicit RegExpValidator(const QRegExp &regexp_accept,
                           const QRegExp &regexp_reject,
                           const QString &replace_string = QString(),
                           QObject *parent = nullptr);
  QValidator::State validate(QString &input, int &pos) const noexcept override;
  void fixup(QString &input) const noexcept override;
 signals:
  /** @brief 验证通过时 会发出此信号 */
  void accepted() const;
  /** @brief 验证不通过时 会发出此信号 */
  void rejected() const;
};

}  // namespace chongying

#endif  // CHONGYING_TOOL_STRINGVALIDATOR_H
