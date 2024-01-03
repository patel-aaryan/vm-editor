#include "command.h"

class Insert : public Command {
  string c;

 public:
  Insert(string c, Document *doc);
  void executeCmd() override;
};

class Enter : public Command {
 public:
  Enter(Document *doc);
  void executeCmd() override;
};

class Backspace : public Command {
 public:
  Backspace(Document *doc);
  void executeCmd() override;
};

class Escape : public Command {
 public:
  Escape(Document *doc);
  void executeCmd() override;
};

class InvalidCommand : public Command {
 public:
  InvalidCommand(Document *doc);
  void executeCmd() override;
};
