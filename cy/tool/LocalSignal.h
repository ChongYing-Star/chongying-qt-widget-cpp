#ifndef CHONGYING_TOOL_LOCALSIGNAL_H
#define CHONGYING_TOOL_LOCALSIGNAL_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QSharedMemory;
class QLocalServer;
QT_END_NAMESPACE

namespace chongying {

/**
 * @brief 本地信号类 用于接受来自本地进程的信号
 * 单向通讯 如需双向请使用原生QLocalServer
 * 此类需要使用网络模块 在pro文件中配置：QT+=network
 */
class LocalSignal : public QObject {
  Q_OBJECT
  QString key_;
  QSharedMemory *sharedmemory_ = nullptr;
  QLocalServer *server = nullptr;

  /** @brief 监听新连接 */
  void onNewConnection();
  /** @brief 监听连接可读信号 */
  void onReadyRead();

 public:
  explicit LocalSignal(const QString &key, QObject *parent = nullptr);

  /** @brief 检查是否是服务端 */
  bool isServer();
  /**
   * @brief 发送本地信号 只有非服务端才会发信号
   * @param signal 本地信号内容
   * @return 如果发送成功 返回true
   */
  bool sendSignal(const QString &signal);

 signals:
  /** @brief 当收到一个本地信号 会发出此信号 只有服务端才会接收信号 */
  void gotSignal(const QString &signal);
};

}  // namespace chongying

#endif  // CHONGYING_TOOL_LOCALSIGNAL_H
