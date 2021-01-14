#include "IconButton.h"

#include <QDebug>
#include <QIcon>
#include <QUrl>
#include <QVariant>

namespace chongying {

const IntString IconButton::TypeStrings({
    {IconButton::Add, QStringLiteral("Add")},
    {IconButton::Remove, QStringLiteral("Remove")},
    {IconButton::Edit, QStringLiteral("Edit")},
    {IconButton::Check, QStringLiteral("Check")},
    {IconButton::Search, QStringLiteral("Search")},
    {IconButton::Refresh, QStringLiteral("Refresh")},
    {IconButton::Query, QStringLiteral("Query")},
});

QString IconButton::icon_normal() const { return m_iconNormal; }

void IconButton::setIcon_normal(const QString &value) {
  m_iconNormal = value;
  QIcon icon = this->icon();
  icon.addFile(value, QSize(), QIcon::Normal);
  this->setIcon(icon);
}

QString IconButton::icon_disabled() const { return m_iconDisabled; }

void IconButton::setIcon_disabled(const QString &value) {
  m_iconDisabled = value;
  QIcon icon = this->icon();
  icon.addFile(value, QSize(), QIcon::Disabled);
  this->setIcon(icon);
}

void IconButton::__init__(const QString &type) {
  QSizePolicy sizePolicy = this->sizePolicy();
  sizePolicy.setVerticalPolicy(QSizePolicy::Fixed);
  this->setSizePolicy(sizePolicy);
  this->setProperty("class", type);
}

IconButton::IconButton(const QString &type, QWidget *parent)
    : QPushButton(parent) {
  this->__init__(type);
}

IconButton::IconButton(const IconButton::Types &type, QWidget *parent)
    : QPushButton(parent) {
  QString type_;
  try {
    type_ = IconButton::TypeStrings.toString(type);
  } catch (...) {
  }
  this->__init__(type_);
}

}  // namespace chongying
