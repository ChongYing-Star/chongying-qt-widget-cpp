#include "StringFormatter.h"

#include <QTextStream>

namespace chongying {

void StringFormatter::compute(const StringFormatter::Originals &original) {
  for (const auto &item : original) {
    this->variables_[item.first] = format(item.second, this->variables_);
  }
}

StringFormatter::StringFormatter(const Originals &original) {
  this->compute(original);
}

StringFormatter::StringFormatter(const QByteArray &bytes) {
  this->compute(read(bytes));
}

QString StringFormatter::format(QString source, const Variables &variables) {
  static QRegExp reg(QStringLiteral(R"(\$\{([\w ]+)\})"));
  int pos = reg.indexIn(source);
  while (pos >= 0) {
    const int &length = reg.cap().length();
    const QString &name = reg.cap(1).trimmed();
    if (variables.contains(name)) {
      const QString &value = variables[name];
      source.replace(pos, length, value);
      pos += value.length();
    } else {
      pos += length;
    }
    pos = reg.indexIn(source, pos);
  }
  return source;
}

static const auto &codec = "utf8";

StringFormatter::Originals StringFormatter::read(const QByteArray &bytes) {
  QTextStream stream(bytes);
  stream.setCodec(codec);
  static QRegExp reg(QStringLiteral(R"(([\w ]+)=(.+))"));
  Originals original;
  while (!stream.atEnd()) {
    if (reg.indexIn(stream.readLine()) >= 0) {
      original << QPair{reg.cap(1).trimmed(), reg.cap(2).trimmed()};
    }
  }
  return original;
}

QByteArray StringFormatter::write(const StringFormatter::Originals &original) {
  QString string;
  QTextStream stream(&string);
  stream.setCodec(codec);
  static const QString &format = QStringLiteral("%1 = %2");
  for (const auto &item : original) {
    stream << format.arg(item.first).arg(item.second) << Qt::endl;
  }
  return string.toUtf8();
}

}  // namespace chongying
