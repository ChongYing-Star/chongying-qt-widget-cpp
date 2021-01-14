#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

namespace chongying {

/**
 * @brief 显示部件接口
 */
class DisplayWidget {
 public:
  virtual ~DisplayWidget();
  /** @brief 设置部件文本 */
  virtual void setupText() = 0;
  /** @brief 刷新部件样式 */
  virtual void setupStyle() {}
};

}  // namespace chongying

#endif  // DISPLAYWIDGET_H
