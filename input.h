#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <memory>
#include <string>

#include "ncurses.h"

using namespace std;

class Command;
class Document;

class Input {
  string inp = "";

  unique_ptr<Command> convertNavigation(Document *doc);
  unique_ptr<Command> convertNavigationInsert(Document *doc);
  unique_ptr<Command> convertDelete(Document *doc, WINDOW *win);
  unique_ptr<Command> convertUpdate(Document *doc);
  unique_ptr<Command> convertClipboard(Document *doc, WINDOW *win);
  unique_ptr<Command> convertColon(Document *doc, WINDOW *win);
  unique_ptr<Command> convertSearch(Document *doc, WINDOW *win);

 public:
  Input() = default;
  Input(char c);
  Input(const string &c);
  unique_ptr<Command> convert(Document *doc, WINDOW *win);
  ~Input() = default;
};
#endif
