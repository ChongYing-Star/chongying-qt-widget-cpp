#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cy/DisplayWidget.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QLabel;
class QStandardItemModel;
class QTreeView;
class QPushButton;
QT_END_NAMESPACE

// 在.h文件中 只声明 而不include 可以提高编译速度
namespace chongying {
class HeaderView;
class IconButton;
class IconButtonHeader;
class MoveHandle;
class NameLine;
class MouseEventFilter;
}  // namespace chongying

// 如果觉得命名空间太长 可以使用别名
namespace cy = chongying;

class MainWindow : public QMainWindow, public cy::DisplayWidget {
  Q_OBJECT
  QTabWidget *tab_widget;
  QWidget *tab1;

  QLabel *label_createline;

  chongying::IconButtonHeader *icon_button_header;
  chongying::IconButton *ibtn_add;
  chongying::IconButton *ibtn_remove;

  QStandardItemModel *item_model;
  QTreeView *item_view;
  cy::HeaderView *header_view;

  QLabel *label_move_handle;
  cy::MoveHandle *movehandle;

  QLabel *label_enter_name;
  cy::NameLine *name_line;
  QPushButton *pbtn_enter_name;

  cy::MouseEventFilter *mouse_event_filter;

  /** @brief 用于重绘滚动区域 */
  void repaintArea();

 public:
  MainWindow(QWidget *parent = nullptr);

  void setupText() override;
};
#endif  // MAINWINDOW_H
