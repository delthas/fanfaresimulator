#pragma once

#define PORT_NO 15051
#define DISCOVER_MSG "fanfaresimulator"

typedef enum {
  SIG_HELLO,
  SIG_NOTE,
  SIG_CHOICE_LOBBY,
  SIG_CHOICE_INSTRUMENT,
  SIG_READY,
  SIG_START,
  SIG_LOBBIES,
  SIG_INSTRUMENTS,
  SIG_PARTITION
} Protocol_sig;
