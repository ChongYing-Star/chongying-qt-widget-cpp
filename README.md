# 重影：Qt小部件（C++）

本项目提供了一些Qt（c++）开发中便捷的类与方法。

## 如何使用

1. 直接将`cy`文件夹放置于项目根目录

2. 在项目文件（.pro）中引入：

``````QMake
include(cy/cy.pri)
``````

3. 引入必要的资源文件，例子：

```QMake
RESOURCES += \
    resources/images.qrc \
    resources/style.qrc \
    translations.qrc
```



## 详细说明

`MainWindow`是一个演示窗口，其中包含了本项目中绝大多数使用方法。

- `cy/DisplayString.*` 
  - `chongying::DisplayString` 提供公共的字符串翻译
- `cy/DisplayWidget.*`
  - `chongying::DisplayWidget` 提供了设置显示字符串和样式的接口 用于动态切换 翻译/样式
- `cy/Global.h` 提供了全局需要的枚举、唯一对象等
- `cy/IntString.*`
  - `chongying::IntString` 提供了整数与字符串双向绑定转换的方法 多用于枚举
- `cy/tool/GuiCreateTool.*` 提供了创建GUI的便捷工具
- `cy/tool/MouseEventFilter.*`
  - `chongying::MouseEventFilter` 提供了部分鼠标事件过滤器 如：中键点击等
- `cy/tool/RegExpValidator.*`
  - `chongying::RegExpValidator` 字符串正则验证纠错器 用于输入框的验证与自动纠错
- `cy/tool/StringFormatter.*`
  - `chongying::StringFormatter` 字符串格式化器 允许在字符串中使用命名变量占位 然后格式化
- `cy/view/HeaderView.*`
  - `chongying::HeaderView` 头部视图 提供了自动调整行列宽高、隐藏行列等功能
- `cy/widget/IconButton.*`
  - `chongying::IconButton` 图标按钮 提供了已实现的单图标按钮 可以使用qss扩展
- `cy/widget/IconButtonHeader.*`
  - `chongying::IconButtonHeader` 图标按钮头部 便捷类 *不需要可以直接删除*
- `cy/widget/MoveHandle.*`
  - `chongying::MoveHandle` 移动手柄 常用于改变相关部件大小
- `cy/widget/nameinput/NameDialog.h`
  - `chongying::NameDialog` 名称输入对话框 这是一个便捷对话框部件 使用NameLine部件
- `cy/widget/nameinput/NameLine.h`
  - `chongying::NameLine` 名称输入框 这是一个便捷部件 用于过滤输入只能包含【字母、数字、下划线和非ASCII字符】的字符串

