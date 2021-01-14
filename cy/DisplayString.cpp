#include "DisplayString.h"

#include <QDir>

#ifdef QT_NETWORK_LIB
#include <QHostInfo>
#else
#include <QProcess>
#endif

namespace chongying {

const IntString DisplayString::ButtonStrings({
    {DisplayString::Ok, QStringLiteral("Ok")},
    {DisplayString::No, QStringLiteral("No")},
    {DisplayString::Yes, QStringLiteral("Yes")},
    {DisplayString::Cancel, QStringLiteral("Cancel")},
    {DisplayString::Refresh, QStringLiteral("Refresh")},
});

const QString DisplayString::HostName = [] {
// 使用QT_NETWORK_LIB宏确定是否引入网络模块
// 如果没有引入 则使用shell来获取
// Windows平台为"ipconfig" Linux平台为"ifconfig"
#if defined(QT_NETWORK_LIB)
  return QHostInfo::localHostName();
#elif defined(Q_OS_WINDOWS)
  QProcess p;
  p.start("cmd", QStringList() << "/C"
                               << "ipconfig"
                               << "/all");
  p.waitForStarted(1000);
  p.waitForFinished(1000);
  QString line =
      QString::fromLocal8Bit(p.readAllStandardOutput()).split("\r\n")[3];
  return line.mid(line.indexOf(':') + 2);
#else
  // 其他平台通过shell获取的功能待补充
  return QString();
#endif
}();

QString DisplayString::ButtonText(const DisplayString::Buttons &button,
                                  const QString &default_) noexcept {
  switch (button) {
    case Buttons::Ok:
      return tr("Ok");
    case Buttons::No:
      return tr("No");
    case Buttons::Yes:
      return tr("Yes");
    case Buttons::Cancel:
      return tr("Cancel");
    case Buttons::Refresh:
      return tr("Refresh");
  }
  return default_;
}

QString DisplayString::ButtonText(const QString &button) noexcept {
  try {
    return ButtonText(ButtonStrings.to<Buttons>(button), button);
  } catch (...) {
    return button;
  }
}

}  // namespace chongying
