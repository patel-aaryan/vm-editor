#include "command.h"

Command::Command(CommandType type, bool undo, Document *display)
    : type{type}, undoable{undo}, display{display} {}

void Command::manageCmd() {
  if (undoable) {
    display->undoPush(*display);
    display->setSaved(false);
  }
  executeCmd();
}
