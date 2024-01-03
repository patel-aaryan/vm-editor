#include "insert.h"

#include <cstddef>
#include <iostream>
using namespace std;

// Insert Class
Insert::Insert(string c, Document *doc)
    : Command(CommandType::Insert, true, doc), c{c} {}

void Insert::executeCmd() {
  string &s = display->content.at(display->cursor.line);
  s.insert(display->cursor.col++, c);
}

// Enter Class
Enter::Enter(Document *doc)
    : Command(CommandType::Enter, true, doc) {}

void Enter::executeCmd() {
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string s = display->content.at(l);
  display->content[l] = s.substr(0, c);
  display->content.insert(
      display->content.begin() + ++l, s.substr(c));
  c = 0;
}

// Backspace Class
Backspace::Backspace(Document *doc)
    : Command(CommandType::Backspace, true, doc) {}

void Backspace::executeCmd() {
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string &s = display->content.at(l);
  if (c > 0) {
    s.erase(--c, 1);
  } else if (l > 0) {
    string &prev = display->content.at(l - 1);
    c = prev.size();
    prev += s;
    display->content.erase(display->content.begin() + l--);
  }
}

// Escape Class
Escape::Escape(Document *doc)
    : Command(CommandType::Backspace, false, doc) {}

void Escape::executeCmd() {
  size_t &c = display->cursor.col;
  if (c > 0) c--;

  display->setCommandMode(true);
}

InvalidCommand::InvalidCommand(Document *doc)
    : Command(CommandType::Invalid, false, doc) {}

void InvalidCommand::executeCmd() {}
