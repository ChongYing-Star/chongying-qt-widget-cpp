#ifndef NAMELINE_H
#define NAMELINE_H

#include <QLineEdit>

#include "../../DisplayWidget.h"

namespace chongying {

/**
 * @brief 名称输入框
 * 这是一个便捷部件
 * 用于过滤输入只能包含【字母、数字、下划线和非ASCII字符】的字符串
 */
class NameLine : public QLineEdit, public DisplayWidget {
  Q_OBJECT
  void tooltip();

 public:
  explicit NameLine(QWidget *parent = nullptr);
  void setupText() override;

 signals:
};

}  // namespace chongying

#endif  // NAMELINE_H
