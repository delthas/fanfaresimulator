
#ifndef FANFARESIMULATOR_SERVER_HPP
#define FANFARESIMULATOR_SERVER_HPP

#include "instrument.hpp"
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <QtNetwork>
#include <QObject>

typedef enum {
  HELLO,
  NOTE,
  CHOICE_LOBBY,
  CHOICE_INSTRUMENT,
  LOBBIES,
  INSTRUMENTS,
  PARTITION
} protocol_sig;

// Waiting for implementation
class Obj {};

typedef Obj Socket;
typedef Obj Synthesizer;
typedef Obj Note;

//

class Server : public QObject {
private:
  QTcpServer *server;
  std::queue<Note> incomingNotes;
  Synthesizer synthesizer;

  std::map<std::string, std::pair<Socket, bool>> clients; // key : username, vale : (socket, isReady)
  std::map<std::string, Instrument> usrToInstrument; // key : username, value : Instrument
  std::map<Instrument, bool> instrumentMap; // key : Instrument, value : available

  void newConnection();

public:
  explicit Server(QObject *parent = Q_NULLPTR);
  void broadcastStart() const;
  void updateInstrumentMap(Instrument i);
  bool addClient(std::string username);
  bool addClient(std::string username, Instrument i);
  void sendPartition(std::string username);
  std::map<Instrument, bool> getInstrumentMap() const;

};

#endif // FANFARESIMULATOR_SERVER_HPP
