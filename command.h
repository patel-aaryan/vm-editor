#ifndef COMMAND_H
#define COMMAND_H
#include <ncurses.h>

#include <map>
#include <stack>

#include "document.h"
using namespace std;

class Document;

enum class CommandType {
  Invalid,
  Navigation,
  Editing,
  Macro,
  File,
  Search,
  Clipboard,
  Scroll,
  Insert,
  Dot,
  SemiColon,
  Undo,
  Enter,
  Backspace,
  Escape,
  Colon
};

class Command {
  CommandType type;
  bool undoable;

 protected:
  Document *display;
  virtual void executeCmd() = 0;

 public:
  Command(CommandType type, bool undo, Document *display);
  void manageCmd();
  virtual ~Command() = default;
};
#endif
