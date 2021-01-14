#include "IntString.h"

namespace chongying {

IntString::IntString(const QList<QPair<int, QString> > &map)
    : numbers_(map.count()), strings_(map.count()) {
  int index = 0;
  for (const QPair<int, QString> &item : map) {
    this->numbers_[index] = item.first;
    this->strings_[index] = item.second;
    ++index;
  }
}

int IntString::toInt(const QString &string) const {
  int index = this->strings_.indexOf(string);
  if (index == -1)
    throw std::out_of_range(QStringLiteral("Nonexistent string: \"%1\".")
                                .arg(string)
                                .toStdString());
  return this->numbers_[index];
}

QString IntString::toString(const int &number) const {
  int index = this->numbers_.indexOf(number);
  if (index == -1)
    throw std::out_of_range(
        QStringLiteral("Nonexistent number: %1.").arg(number).toStdString());
  return this->strings_[this->numbers_.indexOf(number)];
}

}  // namespace chongying
