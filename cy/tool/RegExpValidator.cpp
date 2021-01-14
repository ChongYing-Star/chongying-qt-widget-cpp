#include "RegExpValidator.h"

namespace chongying {

RegExpValidator::RegExpValidator(const QRegExp &regexp_accept,
                                 const QRegExp &regexp_reject,
                                 const QString &replace_string, QObject *parent)
    : QRegExpValidator(regexp_accept, parent),
      regexp_reject_(regexp_reject),
      replace_string_(replace_string) {
  //
}

QValidator::State RegExpValidator::validate(QString &input,
                                            int &pos) const noexcept {
  QValidator::State state = QRegExpValidator::validate(input, pos);
  if (state != QValidator::Acceptable) {
    fixup(input);
    emit rejected();
    return QValidator::Intermediate;
  }
  emit accepted();
  return state;
}

void RegExpValidator::fixup(QString &input) const noexcept {
  if (replace_string_.isEmpty())
    input = input.remove(regexp_reject_);
  else
    input = input.replace(regexp_reject_, replace_string_);
}

}  // namespace chongying
