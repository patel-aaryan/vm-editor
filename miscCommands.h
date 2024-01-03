#include "command.h"

class Undo : public Command {
 public:
  Undo(Document *doc);
  void executeCmd() override;
};
