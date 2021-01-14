#include <QApplication>
#include <QDir>
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

  MainWindow w;
  w.show();
  return a.exec();
}
