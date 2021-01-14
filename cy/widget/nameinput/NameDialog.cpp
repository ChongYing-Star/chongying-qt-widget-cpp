#include "NameDialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "../../DisplayString.h"
#include "NameLine.h"

namespace chongying {

NameDialog::NameDialog(QWidget *parent) : QDialog(parent) {
  this->label = new QLabel;
  this->lineedit = new NameLine;
  this->box = new QDialogButtonBox;
  this->ok = new QPushButton;
  this->cancel = new QPushButton;
  this->box->addButton(this->ok, QDialogButtonBox::AcceptRole);
  this->box->addButton(this->cancel, QDialogButtonBox::RejectRole);

  QVBoxLayout *layout = new QVBoxLayout;
  this->setLayout(layout);
  layout->addWidget(this->label);
  layout->addWidget(this->lineedit);
  layout->addItem(
      new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
  layout->addWidget(this->box);

  QObject::connect(box, &QDialogButtonBox::accepted, this, &QDialog::accept);
  QObject::connect(box, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void NameDialog::setLabelText(const QString &text) {
  this->label->setText(text);
}

void NameDialog::setTextValue(const QString &text) {
  this->lineedit->setText(text);
}

QString NameDialog::labelText() const { return this->label->text(); }

QString NameDialog::textValue() const { return this->lineedit->text(); }

void NameDialog::setupText() {
  this->setWindowTitle(tr("Enter the name"));
  this->label->setText(tr("Name:"));
  this->ok->setText(DisplayString::ButtonText(DisplayString::Ok));
  this->cancel->setText(DisplayString::ButtonText(DisplayString::Cancel));
  this->lineedit->setupText();
  this->lineedit->setWhatsThis(tr("Name input box."));
}

}  // namespace chongying
