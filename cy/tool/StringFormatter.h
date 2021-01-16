#ifndef CHONGYING_TOOL_STRINGFORMATTER_H
#define CHONGYING_TOOL_STRINGFORMATTER_H

#include <QHash>
#include <QString>

namespace chongying {

/**
 * @brief 字符串格式器
 */
class StringFormatter {
 public:
  /** @brief 源数据 具有顺序性的变量定义 用于预定义一些变量 通常用于定义模板 */
  typedef QList<QPair<QString, QString> > Originals;
  /** @brief 变量值 顺序无关的变量定义 用于指明需要的变量值 通常用于定义值 */
  typedef QHash<QString, QString> Variables;

 private:
  Variables variables_;
  void compute(const Originals &original);

 public:
  inline StringFormatter() {}
  /** @brief 从源数据中初始化对象 */
  StringFormatter(const Originals &original);
  /** @brief 从ByteArray中初始化对象 */
  StringFormatter(const QByteArray &bytes);
  /** @brief 使用已有变量格式化指定字符串 */

  inline QString format(const QString &source) const {
    return format(source, this->variables_);
  }
  /** @brief 使用已有变量和指定的源数据格式化指定字符串 */
  inline QString format(const QString &source, const Originals &basic) const {
    return StringFormatter(basic).format(this->format(source));
  }
  /** @brief 使用已有变量和额外的变量值格式化指定字符串 */
  inline QString withExtra(const QString &source,
                           const Variables &variables) const {
    return format(this->format(source), variables);
  }

  /** @brief 使用指定的变量值格式化指定字符串 */
  static QString format(QString source, const Variables &variables);

  /** @brief 从ByteArray中读取源数据 */
  static Originals read(const QByteArray &bytes);
  /** @brief 将源数据写入ByteArray */
  static QByteArray write(const Originals &original);
};

/** @brief 重载了 % 运算符 */
inline QString operator%(const QString &source,
                         const StringFormatter &formatter) {
  return formatter.format(source);
}
inline QString operator%(const QString &source,
                         const StringFormatter::Variables &variables) {
  return StringFormatter::format(source, variables);
}

}  // namespace chongying

#endif  // CHONGYING_TOOL_STRINGFORMATTER_H
