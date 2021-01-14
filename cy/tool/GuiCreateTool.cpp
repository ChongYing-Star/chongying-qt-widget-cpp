#include "GuiCreateTool.h"

namespace chongying {
namespace GuiCreateTool {

QFrame *CreateLine(QFrame::Shape shape) noexcept {
  QFrame *line = new QFrame;
  line->setFrameShape(shape);
  line->setFrameShadow(QFrame::Sunken);
  return line;
}

}  // namespace GuiCreateTool
}  // namespace chongying
