#include "editing.h"

// Editing Class
Editing::Editing(Document *doc) : Command(CommandType::Editing, true, doc) {}

void Editing::executeCmd() { manageEditing(); }

// DELETE CLASS
void Delete::manageEditing() { executeDelete(); }

// Delete Subclasses

void sCmd::executeDelete() {
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

void ddCmd::executeDelete() {
  if (display->content[0].empty()) return;
  size_t &l = display->cursor.line;
  if (display->content.size() == 1) {
    display->content[0].clear();
  } else {
    display->content.erase(display->content.begin() + l);
    while (l > display->content.size() - 1) l--;
  }
  display->cursor.col = 0;
}

void ccCmd::executeDelete() {
  size_t &l = display->cursor.line;
  display->content[l].clear();
  display->cursor.col = 0;
  display->setCommandMode(false);
}

void cDollar::executeDelete() {
  string &s = display->content[display->cursor.line];
  size_t toRemove = s.size() - display->cursor.col;
  s.erase(display->cursor.col, toRemove);
  display->setCommandMode(false);
}

void dwCmd::executeDelete() {
  string &s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  size_t endIndex;
  bool deleteSpaces = false;
  for (endIndex = c; endIndex < s.size(); endIndex++) {
    char &ch = s[endIndex];
    if ((ch == ' ' && !deleteSpaces && endIndex != c) || (ch != ' ' && deleteSpaces)) break;
    if (ch == ' ') {
      if (endIndex == c) deleteSpaces = true;
    }
  }
  s.erase(c, endIndex - c);
}

void diwCmd::executeDelete() {
  string &s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  size_t startIndex = c, endIndex = c;
  if (s[c] == ' ') {
    while (startIndex > 0 && s[startIndex - 1] == ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] == ' ') endIndex++;
  } else {
    while (startIndex > 0 && s[startIndex - 1] != ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] != ' ') endIndex++;
  }
  s.erase(startIndex, endIndex - startIndex);
  if (s[c] != ' ') c = startIndex;
}

void dawCmd::executeDelete() {
  string &s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  size_t startIndex = c, endIndex = c;
  if (s[c] == ' ') {
    while (startIndex > 0 && s[startIndex - 1] == ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] == ' ') endIndex++;
    s.erase(startIndex, endIndex - startIndex);
  } else {
    while (startIndex > 0 && s[startIndex - 1] != ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] != ' ') endIndex++;
    s.erase(startIndex, endIndex - startIndex);
    c = startIndex;

    endIndex = startIndex;
    while (endIndex < s.size() && s[endIndex] == ' ') endIndex++;
    s.erase(startIndex, endIndex - startIndex);
  }
}

void dhCmd::executeDelete() {
  string &s = display->content[display->cursor.line];
  if (s.empty() || display->cursor.col == 0) return;
  s.erase(--display->cursor.col, 1);
}

void dlCmd::executeDelete() {
  string &s = display->content[display->cursor.line];
  if (s.empty() || display->cursor.col == s.size() - 1) return;
  s.erase(display->cursor.col, 1);
}

void djCmd::executeDelete() {
  size_t &l = display->cursor.line;
  auto b = display->content.begin();
  display->cursor.col = 0;
  if (l == display->content.size() - 1) return;
  display->content.erase(b + l, b + l + 2);
  while (l > 0 && l >= display->content.size()) l--;
  if (display->content.empty()) display->content.push_back("");
}

void dkCmd::executeDelete() {
  size_t &l = display->cursor.line;
  auto b = display->content.begin();
  display->cursor.col = 0;
  if (l == 0 || display->content.size() < 2) return;
  display->content.erase(b + l - 1, b + l + 1);
  while (l > 0 && l >= display->content.size()) l--;
  if (display->content.empty()) display->content.push_back("");
}

void cjCmd::executeDelete() {
  size_t &l = display->cursor.line;
  if (l == display->content.size() - 1) return;
  auto b = display->content.begin();
  display->cursor.col = 0;
  display->content.erase(b + l + 1, b + l + 2);
  display->content[l].clear();
  display->setCommandMode(false);
}

void ckCmd::executeDelete() {
  size_t &l = display->cursor.line;
  if (l == 0 || display->content.size() < 2) return;
  auto b = display->content.begin();
  display->cursor.col = 0;
  display->content.erase(b + l - 1, b + l);
  l--;
  display->content[l].clear();
  display->setCommandMode(false);
}

// UPDATE CLASS
void Update::manageEditing() { executeUpdate(); }

// Update Subclasses
void oCmd::executeUpdate() {
  display->content.insert(display->content.begin() + ++display->cursor.line, "");
  display->cursor.col = 0;
  display->setCommandMode(false);
}

void OCmd::executeUpdate() {
  display->content.insert(display->content.begin() + display->cursor.line, "");
  display->cursor.col = 0;
  display->setCommandMode(false);
}

void JCmd::executeUpdate() {
  size_t &l = display->cursor.line;
  if (l + 1 < display->content.size()) {
    display->cursor.col = display->content[l].size();
    display->content[l] += " " + display->content[l + 1];
    display->content.erase(display->content.begin() + l + 1);
  }
}

void rCmd::executeUpdate() {
  display->content[display->cursor.line][display->cursor.col] = c;
}
