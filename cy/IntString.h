#ifndef INTSTRING_H
#define INTSTRING_H

#include <QHash>
#include <QString>

namespace chongying {

/**
 * @brief 提供了整数与字符串双向绑定转换的方法 多用于枚举
 */
class IntString {
  QVector<int> numbers_;
  QVector<QString> strings_;

 public:
  /** @brief 构造函数 需要提供整数与字符串的关系表 */
  IntString(const QList<QPair<int, QString> > &map);

  /** @brief 获取全部整数 用于遍历 */
  inline QVector<int> numbers() const noexcept { return this->numbers_; }
  /** @brief 获取全部字符串 用于遍历 */
  inline QVector<QString> strings() const noexcept { return this->strings_; }

  /** @brief 检查字符串是否存在 */
  bool contains(const QString &string) const noexcept {
    return this->strings_.contains(string);
  }
  /** @brief 检查整数是否存在 */
  bool contains(const int &number) const noexcept {
    return this->numbers_.contains(number);
  }

  /**
   * @brief 提供由字符串向整数的转换
   * 当提供的字符串不存在时抛出std::out_of_range异常
   * @exception std::out_of_range
   */
  int toInt(const QString &string) const;
  /**
   * @brief 提供由字符串向整数的转换
   * 当提供的字符串不存在时抛出std::out_of_range异常
   * @exception std::out_of_range
   */
  inline int operator[](const QString &string) const { return toInt(string); }

  /**
   * @brief 提供由整数向字符串的转换
   * 当提供的整数不存在时抛出std::out_of_range异常
   * @exception std::out_of_range
   */
  QString toString(const int &number) const;
  /**
   * @brief 提供由整数向字符串的转换
   * 当提供的整数不存在时抛出std::out_of_range异常
   * @exception std::out_of_range
   */
  inline QString operator[](const int &number) const {
    return toString(number);
  }

  /**
   * @brief 提供由字符串向指定类型的转换（由int强制转换 通常是枚举类型）
   * 当提供的字符串不存在时抛出std::out_of_range异常
   * @exception std::out_of_range
   */
  template <typename T>
  inline T to(const QString &string) const {
    return static_cast<T>(toInt(string));
  }
};

}  // namespace chongying

#endif  // INTSTRING_H
