#ifndef CHONGYING_WIDGET_NAMEINPUT_NAMEDIALOG_H
#define CHONGYING_WIDGET_NAMEINPUT_NAMEDIALOG_H

#include <QDialog>

#include "../../DisplayWidget.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QDialogButtonBox;
QT_END_NAMESPACE

namespace chongying {

class NameLine;

/**
 * @brief 名称输入对话框
 * 这是一个便捷对话框部件
 * 使用NameLine部件 过滤输入只能包含【字母、数字、下划线和非ASCII字符】的字符串
 */
class NameDialog : public QDialog, public DisplayWidget {
  Q_OBJECT
  QLabel *label;
  NameLine *lineedit;
  QDialogButtonBox *box;
  QPushButton *ok;
  QPushButton *cancel;

 public:
  explicit NameDialog(QWidget *parent = nullptr);
  void setLabelText(const QString &text);
  void setTextValue(const QString &text);
  QString labelText() const;
  QString textValue() const;

  void setupText() override;

 signals:
};

}  // namespace chongying

#endif  // CHONGYING_WIDGET_NAMEINPUT_NAMEDIALOG_H
