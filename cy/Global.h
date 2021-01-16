#ifndef CHONGYING_GLOBAL_H
#define CHONGYING_GLOBAL_H

namespace chongying {

namespace CyGlobal {

/** @brief 数据角色频道 */
enum ItemDataRoleChannel {
  /** @brief 存储频道 */
  ContainerChannel = 0x70010000,
  /** @brief 视图频道 */
  ViewChannel = 0x70020000,
  /** @brief 交互频道 */
  InteractiveChannel = 0x70030000,

  /** @brief 扩展角色频道开始值 */
  UserChannel = 0x71000000,
};

/** @brief 扩展数据角色 */
enum ItemDataRole {
  /** @brief 扩展数据角色::保存文件路径 (QString) */
  FilePathRole = 0x0021 | ItemDataRoleChannel::ContainerChannel,
  /** @brief 扩展数据角色::保存原始名称 (QString) */
  NameRole = 0x0022 | ItemDataRoleChannel::ContainerChannel,

  // ! HeaderView
  /** @brief 扩展数据角色::保存大小 (int) */
  SizeRole = 0x0011 | ItemDataRoleChannel::ViewChannel,
  /** @brief 扩展数据角色::保存填充宽度权重 (int) */
  FillRole = 0x0012 | ItemDataRoleChannel::ViewChannel,
  /** @brief 扩展数据角色::保存是否隐藏 (bool) */
  HideRole = 0x0021 | ItemDataRoleChannel::ViewChannel,
  /** @brief 扩展数据角色::保存排序值 (int) */
  SortRole = 0x0011 | ItemDataRoleChannel::ViewChannel,
};

}  // namespace CyGlobal

}  // namespace chongying

#endif  // CHONGYING_GLOBAL_H
