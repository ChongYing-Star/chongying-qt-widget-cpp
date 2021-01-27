#include <cy/tool/LocalSignal.h>
#include <cy/tool/StringFormatter.h>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QTimer>
#include <QTranslator>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // 由于多次注册qss会使之前注册的失效 需要全部读取后一次性注册

  // 遍历获取所有qss文件
  // 注意：本示范没有考虑文件的先后关系 使用了默认的文件名顺序
  //      实际应用时 后文覆盖前文 用户自定文件需要靠后读取
  std::function<QStringList(QDir)> List_file = [&](QDir dir) -> QStringList {
    QListIterator<QFileInfo> iterator(dir.entryInfoList());
    QStringList filePaths;
    while (iterator.hasNext()) {
      QFileInfo info = iterator.next();
      if (info.isDir())
        filePaths += List_file(QDir(info.absoluteFilePath()));
      else if (info.isFile())
        filePaths += info.absoluteFilePath();
    }
    return filePaths;
  };
  QStringList style_files = List_file(QDir(QStringLiteral(":/Styles")));
  // 读取所有qss文件至同一字符串中
  QString qss;
  for (const auto &filepath : style_files) {
    QFile file(filepath);
    file.open(QFile::ReadOnly);
    qss.append(QString::fromLatin1(file.readAll()));
  }
  // 一次性注册
  qApp->setStyleSheet(qss);

  QStringList translations = {
      ":/translations/chongying_zh_CN.qm",
      ":/translations/zh_CN.qm",
  };
  for (const auto &filepath : translations) {
    QTranslator *translator = new QTranslator(qApp);
    if (translator->load(filepath)) qApp->installTranslator(translator);
  }

  // LocalSignal 使用例：
  /** @brief 应用名 */
  QString ApplicationName = "chongying-qt-widget-cpp";
  /** @brief 此信号用于保证应用唯一启动 使用应用名作为连接标识 */
  chongying::LocalSignal forOnly(ApplicationName);
  if (!forOnly.isServer()) {
    // 当此对象非服务器时 说明此时已有应用运行 发送激活信号
    forOnly.sendSignal("activate");
    // 退出应用
    return 0;
  }
  // 服务端 接受激活信号 执行激活窗口操作
  QObject::connect(&forOnly, &chongying::LocalSignal::gotSignal,
                   [](QString signal) {
                     if (signal == "activate") {
                       for (QWidget *window : qApp->topLevelWidgets()) {
                         if (qobject_cast<QMainWindow *>(window)) {
                           if (window->isHidden()) window->show();
                           window->raise();
                           window->activateWindow();
                         }
                       }
                     }
                   });
  MainWindow w;
  w.show();

  // StringFormatter 使用例:
  {
    // 源数据可以定义一些格式化模板 他们之间可以存在依赖 但必须是后值依赖前值
    // 允许将源数据格式化写入文件 这里使用字符串代替
    QString file(R"(
home            =   /home/chongying
qt_dirpath      =   ${home}/Qt
web_dirname     =   www
filepath        =   ${qt_dirpath}/${filename}
)");
    // 使用chongying::StringFormatter::read方法可以将如上格式的定义转换为源数据
    chongying::StringFormatter::Originals originals =
        chongying::StringFormatter::read(file.toUtf8());
    // 格式化器的实例化需要提供源数据 （但通常可以不实例化
    chongying::StringFormatter formatter(originals);
    // 定义最终变量 它通常是运行过程中产生的
    chongying::StringFormatter::Variables variables{
        {"filename", "test.h"},
        {"hostname", "chongying.studio"},
    };

    {
      // 可以使用{}代码块来限制using的作用范围
      using chongying::operator%;
      qDebug() << "1. 引入命名空间中的运算符重载后 直接使用%运算符格式化：";

      qDebug() << "${home}/helloworld/${undefined}" % formatter;
      // >> "/home/chongying/helloworld/${undefined}"

      qDebug() << "${filepath}" % originals % variables;
      // >> "/home/chongying/Qt/test.h"

      qDebug() << "${home}/${web_dirname}/${hostname}" % formatter % variables;
      // >> "/home/chongying/www/chongying.studio"

      qDebug() << "[${date}]${name}.txt" %
                      chongying::StringFormatter::Variables{
                          {"date", "2021-01-16"},
                          {"name", "SunnyDay"},
                      };
      // >> "[2021-01-16]SunnyDay.txt"
    }
    {
      qDebug() << "2. 使用方法来格式字符串：";

      qDebug() << formatter.format("${home}/helloworld/${undefined}");
      // >> "/home/chongying/helloworld/${undefined}"

      qDebug() << chongying::StringFormatter::format(
          formatter.format("${filepath}"), variables);
      // >> "/home/chongying/Qt/test.h"

      qDebug() << formatter.withExtra("${home}/${web_dirname}/${hostname}",
                                      variables);
      // >> "/home/chongying/www/chongying.studio"

      qDebug() << chongying::StringFormatter::format(
          "[${date}]${name}.txt", chongying::StringFormatter::Variables{
                                      {"date", "2021-01-16"},
                                      {"name", "SunnyDay"},
                                  });
      // >> "[2021-01-16]SunnyDay.txt"
    }
  }

  return a.exec();
}
