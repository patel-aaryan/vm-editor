#include "navigation.h"

// Navigation Class
Navigation::Navigation(Document *doc)
    : Command(CommandType::Navigation, false, doc),
      docLine{doc->cursor.line},
      docCol{doc->cursor.col} {}

void Navigation::executeCmd() { manageNavigation(); }

// Subclasses
void hCmd::manageNavigation() {
  if (docCol > 0) docCol--;
}

void jCmd::manageNavigation() {
  if (docLine < display->content.size() - 1) docLine++;
  size_t lineLength = display->content[docLine].size();
  if (lineLength < docCol) docCol = lineLength;
}

void kCmd::manageNavigation() {
  if (docLine > 0) docLine--;
  size_t lineLength = display->content[docLine].size();
  if (lineLength < docCol) docCol = lineLength;
}

void lCmd::manageNavigation() {
  if (docCol < display->content[docLine].size()) docCol++;
}

void aCmd::manageNavigation() {
  if (docCol < display->content[docLine].size()) ++docCol;
}

void Dollar::manageNavigation() { docCol = display->content[docLine].size(); }

void Chevron::manageNavigation() { docCol = 0; }

void bCmd::manageNavigation() {
  string s = display->content[docLine];
  bool done = false;
  bool whitespace = false;
  while (!done) {
    if (docCol == 0) {
      if (docLine == 0 || (s[docCol] != ' ' && whitespace)) {
        done = true;
      } else {
        s = display->content[--docLine];
        docCol = s.size();
        whitespace = true;
      }
    } else if (s[docCol - 1] == ' ' && whitespace) {
      done = true;
    } else {
      if (s[docCol - 1] != ' ') whitespace = true;
      docCol--;
    }
  }
}

void wCmd::manageNavigation() {
  string s = display->content[docLine];
  bool done = false;
  bool whitespace = false;
  while (!done) {
    if (docCol == s.size()) {
      if (docLine + 1 == display->content.size()) {
        done = true;
      } else {
        s = display->content[++docLine];
        docCol = 0;
        whitespace = true;
      }
    } else if (s[docCol] != ' ' && whitespace) {
      done = true;
    } else {
      if (s[docCol] == ' ') whitespace = true;
      docCol++;
    }
  }
}

void fCmd::manageNavigation() {
  string &s = display->content[display->cursor.line];
  size_t c = s.find(ch, display->cursor.col + 1);
  if (c != string::npos) display->cursor.col = c;
}

void FCmd::manageNavigation() {
  if (display->cursor.col == 0) return;
  string &s = display->content[display->cursor.line];
  size_t c = display->cursor.col - 1;
  while (c > 0 && s[c] != ch) c--;
  if (s[c] == ch) display->cursor.col = c;
}

map<char, char> brackets = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

void Percent::manageNavigation() {
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string s = display->content[l];

  for (size_t i = c; i < s.size(); i++) {
    try {
      bracket = brackets.at(s[i]);
      break;
    } catch (...) {
    }
  }
  if (bracket == ' ') return;
  size_t pos = s.find(bracket, c);
  while (l < display->content.size() - 1 && pos == string::npos) {
    l++;
    s = display->content[l];
    pos = s.find(bracket);
  }
  if (pos == string::npos) return;
  c = pos;
}
