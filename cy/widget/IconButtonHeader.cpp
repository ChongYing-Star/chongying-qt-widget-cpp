#include "IconButtonHeader.h"

#include <QLabel>
#include <QLayout>
#include <QPainter>
#include <QStyleOption>

namespace chongying {

void IconButtonHeader::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

IconButtonHeader::IconButtonHeader(QWidget *parent) : QWidget(parent) {
  this->layout = new QHBoxLayout;
  this->setLayout(this->layout);
  this->layout->setSpacing(0);
  this->layout->setMargin(0);

  this->label = new QLabel;
  this->layout->addWidget(this->label);
  QSizePolicy policy = this->label->sizePolicy();
  policy.setHorizontalPolicy(QSizePolicy::Expanding);
  this->label->setSizePolicy(policy);
}

void IconButtonHeader::setText(const QString &text) {
  return this->label->setText(text);
}

QString IconButtonHeader::text() const { return this->label->text(); }

IconButton *IconButtonHeader::addButton(const IconButton::Types &type,
                                        const QString &tooltip) {
  IconButton *button = new IconButton(type);
  button->setToolTip(tooltip);
  this->layout->addWidget(button);
  this->buttons.append(button);
  return button;
}

IconButton *IconButtonHeader::addButton(const QString &type,
                                        const QString &tooltip) {
  IconButton *button = new IconButton(type);
  button->setToolTip(tooltip);
  this->layout->addWidget(button);
  this->buttons.append(button);
  return button;
}

}  // namespace chongying
