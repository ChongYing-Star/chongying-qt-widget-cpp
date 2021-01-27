#include "LocalSignal.h"

// 需要使用网络模块 在pro文件中配置：QT += network
#include <QLocalServer>
#include <QLocalSocket>
#include <QSharedMemory>

namespace chongying {

void LocalSignal::onNewConnection() {
  QLocalSocket *newsocket = this->server->nextPendingConnection();
  QObject::connect(newsocket, &QLocalSocket::readyRead, this,
                   &LocalSignal::onReadyRead);
}

void LocalSignal::onReadyRead() {
  QLocalSocket *local = static_cast<QLocalSocket *>(sender());
  if (!local) return;
  QTextStream in(local);
  emit gotSignal(in.readAll());
}

LocalSignal::LocalSignal(const QString &key, QObject *parent)
    : QObject(parent), key_(key) {
  this->sharedmemory_ = new QSharedMemory(this->key_, this);
  if (sharedmemory_->attach()) {
    sharedmemory_->detach();
  } else {
    sharedmemory_->create(1);
    QLocalServer::removeServer(this->key_);
    this->server = new QLocalServer(this);
    this->server->listen(this->key_);
    QObject::connect(this->server, &QLocalServer::newConnection, this,
                     &LocalSignal::onNewConnection);
  }
}

bool LocalSignal::isServer() { return this->server != nullptr; }

bool LocalSignal::sendSignal(const QString &signal) {
  if (this->isServer()) return false;
  QLocalSocket socket;
  socket.connectToServer(this->key_);
  if (socket.waitForConnected()) {
    QTextStream ts(&socket);
    ts << signal;
    ts.flush();
    if (socket.waitForBytesWritten(3000)) return true;
  }
  return false;
}

}  // namespace chongying
