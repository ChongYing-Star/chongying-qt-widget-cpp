#ifndef GUICREATETOOL_H
#define GUICREATETOOL_H

#include <QFrame>

namespace chongying {

/**
 * @brief 创建GUI工具
 */
namespace GuiCreateTool {
/**
 * @brief 创建一条线
 * @param shape 形状
 * @return 对象
 */
QFrame *CreateLine(QFrame::Shape shape) noexcept;
}  // namespace GuiCreateTool

}  // namespace chongying

#endif  // GUICREATETOOL_H
