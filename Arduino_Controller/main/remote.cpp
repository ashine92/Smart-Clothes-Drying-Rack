// remote.cpp
#include "remote.h"

bool remoteControl = false;
int remoteCmd = -1;

void handleRemoteCommand(String cmd) {
  if (cmd == "1") {
    remoteControl = true;
    remoteCmd = 1;
  } else if (cmd == "0") {
    remoteControl = true;
    remoteCmd = 0;
  } else {
    remoteControl = false;
    remoteCmd = -1;
  }
}
