#include "../include/network/server.hpp"

/* PRIVATE */
void NetworkServer::newConnection() {
  QTcpSocket *clientConnection = server->nextPendingConnection();
  connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);

  std::string username = "";
  ServerConnection *client = new ServerConnection(username, clientConnection, this);
  clients.push_back(client);
  std::cout << "new client" << std::endl;

  // clientConnection->write("Hello you !\n");
  // clientConnection->disconnectFromHost();
}

void NetworkServer::sendJsonObject(std::string username, QJsonObject obj) {
  for (size_t i = 0; i < clients.size(); i++) {
    if (clients[i]->getUsername() == username) {
      QJsonDocument doc = QJsonDocument(obj);
      QByteArray msg = doc.toJson(JSON_FORMAT);
      clients[i]->write(msg);
      return;
    }
  }
  printf("Not such client found: %s\n", username.c_str());
}

void NetworkServer::broadcast(QJsonObject obj) {
  QJsonDocument doc = QJsonDocument(obj);
  QByteArray msg = doc.toJson();
  // for each element e of the Set clients
  for (size_t i = 0; i < clients.size(); i++) {
    clients[i]->write(msg);
  }
}

/* PUBLIC */
NetworkServer::NetworkServer(QObject *parent) : QObject(parent) {
  server = new QTcpServer(this);

  connect(server, &QTcpServer::newConnection, this, &NetworkServer::newConnection);

  if(server->listen(QHostAddress::Any, PORT_NO) == 0) {
    exit(EXIT_FAILURE);
  }
  std::cout << "NetworkServer Online ! on port: " << PORT_NO << std::endl;
}

void NetworkServer::broadcastStart() {
  QJsonObject obj;
  obj["type"] = SIG_START;
  broadcast(obj);
}

void NetworkServer::sendPartition(std::string username, Partition partition) {
  QJsonObject obj;
  obj["type"] = SIG_PARTITION;
  obj["data"] = partitionToJson(partition);
  sendJsonObject(username, obj);
}

void NetworkServer::sendPupitres(std::string username, std::map<Pupitre, bool> pupitres) {
  QJsonObject obj;
  obj["type"] = SIG_PUPITRES;
  QJsonArray JsonPupitre;
  for (auto & pair : pupitres) {
    JsonPupitre.append(pupitreToJson(pair.first, pair.second));
  }
  obj["data"] = JsonPupitre;
  sendJsonObject(username, obj);
}
