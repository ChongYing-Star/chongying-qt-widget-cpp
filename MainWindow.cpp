#include "MainWindow.h"

#include <cy/Global.h>
#include <cy/tool/GuiCreateTool.h>
#include <cy/tool/MouseEventFilter.h>
#include <cy/view/HeaderView.h>
#include <cy/widget/IconButtonHeader.h>
#include <cy/widget/MoveHandle.h>
#include <cy/widget/nameinput/NameDialog.h>
#include <cy/widget/nameinput/NameLine.h>

#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QTimer>
#include <QTreeView>

void MainWindow::repaintArea() {
  QWidget *widget = tab1;
  // 由于改变小部件大小需要到下一个事件循环才生效
  // 此处利用Qt特性 使用延时0毫秒来到达下一个事件循环
  QTimer::singleShot(
      0, [widget]() { widget->setFixedHeight(widget->sizeHint().height()); });
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  tab_widget = new QTabWidget;
  setCentralWidget(tab_widget);
  resize(1000, 600);

  auto tab1_ = new QScrollArea;
  tab_widget->addTab(tab1_, "tab1");
  tab1_->setWidgetResizable(true);
  tab1 = new QWidget;
  tab1_->setWidget(tab1);
  auto tab1_layout = new QVBoxLayout(tab1);

  label_createline = new QLabel;
  // 使用<cy/tool/GuiCreateTool.h>chongying::GuiCreateTool::CreateLine创建一条线：
  tab1_layout->addWidget(label_createline);
  tab1_layout->addWidget(cy::GuiCreateTool::CreateLine(QFrame::HLine));

  // 使用<cy/widget/IconButtonHeader.h>chongying::IconButtonHeader创建一个带有图标按钮的标题：
  icon_button_header = new cy::IconButtonHeader;
  // 可以使用自定义的字符串 但需要在qss中指明对应图标
  ibtn_add = icon_button_header->addButton("Add");
  ibtn_remove = icon_button_header->addButton(cy::IconButton::Remove);
  icon_button_header->addButton(cy::IconButton::Refresh);
  tab1_layout->addWidget(icon_button_header);

  item_model = new QStandardItemModel;
  item_view = new QTreeView;
  header_view = new cy::HeaderView;
  item_view->setModel(item_model);
  item_view->setHeader(header_view);
  tab1_layout->addWidget(item_view);

  for (int i = 0; i < 5; ++i) {
    QStandardItem *item = new QStandardItem;
    item_model->setHorizontalHeaderItem(i, item);
    // 设置大小权重
    if (i == 0) item->setData(2, cy::CyGlobal::FillRole);
    if (i == 1) item->setData(1, cy::CyGlobal::FillRole);
    // 设置默认大小
    if (i == 2) item->setData(300, cy::CyGlobal::SizeRole);
    // 设置默认隐藏
    if (i == 4) item->setData(true, cy::CyGlobal::HideRole);
  }
  item_model->appendRow({
      new QStandardItem("First data"),
      new QStandardItem("some data"),
      new QStandardItem("some data"),
      new QStandardItem("some data"),
      new QStandardItem("Hidden data"),
  });

  label_move_handle = new QLabel;
  tab1_layout->addWidget(label_move_handle);
  movehandle = new cy::MoveHandle(Qt::Vertical);
  tab1_layout->addWidget(movehandle);
  // 想要移动手柄生效 必须监听MoveHandle::moved信号
  // 然后在对应的槽函数中改变相关小部件的大小 并在下一个事件循环中重绘小部件
  connect(movehandle, &cy::MoveHandle::moved, [this](const int &distance) {
    auto widget = this->item_view;
    auto height = widget->height() + distance;
    // 此处可以限制部件的最小大小
    // 不必担心此举使鼠标移出移动手柄的所在位置 而造成计算错误
    // 参数distance得到是相对鼠标按下时位置的距离
    if (height < 100) {
      height = 100;
    }
    widget->setFixedHeight(height);
    this->repaintArea();
  });

  label_enter_name = new QLabel;
  tab1_layout->addWidget(label_enter_name);
  name_line = new cy::NameLine;
  pbtn_enter_name = new QPushButton;
  auto *name_layout = new QHBoxLayout;
  name_layout->addWidget(name_line);
  name_layout->addWidget(pbtn_enter_name);
  tab1_layout->addLayout(name_layout);
  connect(pbtn_enter_name, &QPushButton::clicked, [this] {
    cy::NameDialog dialog(this);
    dialog.setupText();  // 需要显式调用
    auto flag = dialog.exec();
    QString string = dialog.textValue();
    if (flag == QDialog::Accepted && !string.isEmpty()) {
      this->name_line->setText(string);
    }
  });

  QWidget *tab2 = new QWidget;
  tab_widget->addTab(tab2, "");
  mouse_event_filter = new cy::MouseEventFilter(tab_widget);
  tab_widget->tabBar()->installEventFilter(mouse_event_filter);
  connect(mouse_event_filter, &cy::MouseEventFilter::middleClicked,
          [this](const QPoint &point) {
            auto index = this->tab_widget->tabBar()->tabAt(point);
            QMessageBox::information(this, tr("Middle clicked"),
                                     tr("You middle clicked %1.").arg(index));
            // 可以用作中键关闭标签页 如下：
            // this->tab_widget->removeTab(index);
          });

  repaintArea();

  setupText();
}

// 此方法继承自chongying::DisplayWidget接口
// 所有显示的字符串应当在此方法中设置 当重新载入翻译文件后 应当调用此方法
// 子部件中若有chongying::DisplayWidget 同样在此方法中调用
void MainWindow::setupText() {
  label_createline->setText(
      tr("Use "
         "<cy/tool/GuiCreateTool.h>"
         "chongying::GuiCreateTool::CreateLine"
         " to create a line:"));

  icon_button_header->setText(
      tr("Use "
         "<cy/widget/IconButtonHeader.h>"
         "chongying::IconButtonHeader"
         " to create a head with icon buttons"));
  ibtn_add->setToolTip(tr("Add button"));
  ibtn_remove->setToolTip(tr("Remove button"));

  QStringList header_labels{
      tr("First cannot hidden"),          // 第一列（行）不可隐藏
      tr("Right click to context menu"),  // 右键点击头部展开菜单
      tr("Hide or show in context menu"),  // 在菜单中隐藏或显示列（行）
      tr("Or resize"),                     // 或者调整列（行）的大小
      tr("Hide by default"),               // 默认隐藏的列（行）
  };
  // 先从模型中获取QStandardItem 重设item的文本
  // 这样可以避免破坏记录的大小和是否隐藏的数据
  for (int i = 0, count = header_labels.count(); i < count; ++i) {
    QStandardItem *item = item_model->horizontalHeaderItem(i);
    if (item) item->setText(header_labels[i]);
  }

  // 拖动移动手柄可以改变视图大小 他们不必相邻
  label_move_handle->setText(
      tr("Drag the MoveHandle to resize the view."
         "They don't have to be adjacent."));

  label_enter_name->setText(tr("Enter name:"));
  name_line->setupText();  // 调用子部件的相同方法
  pbtn_enter_name->setText(tr("Enter name by dialog"));

  tab_widget->setTabText(1, tr("Middle click tab"));
}
