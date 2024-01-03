#include "miscCommands.h"

Undo::Undo(Document *doc) : Command(CommandType::Backspace, false, doc) {}

void Undo::executeCmd() { display->doUndo(); }
