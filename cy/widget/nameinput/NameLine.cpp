#include "NameLine.h"

#include <QToolTip>

#include "../../tool/RegExpValidator.h"

namespace chongying {

void NameLine::tooltip() {
  QPoint point = this->rect().bottomLeft();
  point = this->mapToGlobal(point);
  point.ry() -= 10;
  QToolTip::showText(
      point, tr("Alphanumeric & underscores & non ASCII characters"), this);
}

NameLine::NameLine(QWidget *parent) : QLineEdit(parent) {
  RegExpValidator *v = new RegExpValidator(
      QRegExp(R"(([^\x00-\x7f]|[\w])*)"),
      QRegExp(R"([\x00-\x2F\x3A-\x40\x5B-\x5E\x60\x7B-\x7F])"), QString(),
      this);
  this->setValidator(v);
  connect(v, &RegExpValidator::rejected, this, &NameLine::tooltip);
  connect(v, &RegExpValidator::accepted, &QToolTip::hideText);
}

void NameLine::setupText() {
  this->setPlaceholderText(
      tr("Alphanumeric & underscores & non ASCII characters"));
}

}  // namespace chongying
