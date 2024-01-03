#include "clipboard.h"

Clipboard::Clipboard(Document *doc, bool undo)
    : Command(CommandType::Clipboard, undo, doc) {}

void Clipboard::executeCmd() { manageClipboard(); }

void xCmd::manageClipboard() {
  display->copyLine = false;
  string &s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  string toCopy;
  toCopy = s[c];
  s.erase(c, 1);
  display->addClipboard(toCopy);
}

void XCmd::manageClipboard() {
  display->copyLine = false;
  string &s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  string toCopy;
  if (c > 0) {
    toCopy = s[c - 1];
    s.erase(c - 1, 1);
    display->addClipboard(toCopy);
  }
  if (c > 0) c--;
}

void pCmd::manageClipboard() {
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string &s = display->content[l];
  string toPaste = display->getClipboard();
  if (toPaste.size() == 0) return;
  if (display->copyLine) {
    if (l < display->content.size()) l++;
    display->content.insert(display->content.begin() + l, toPaste);
  } else if (s.size() == 0) {
    s = toPaste;
  } else if (c == s.size()) {
    toPaste.insert(0, " ");
    s.insert(c, toPaste);
  } else if (c < s.size()) {
    s.insert(c + 1, toPaste);
  }
  c += toPaste.size();
}

void PCmd::manageClipboard() {
  size_t &l = display->cursor.line;
  string toPaste = display->getClipboard();
  if (display->copyLine) {
    display->content.insert(display->content.begin() + l, toPaste);
  } else {
    string &s = display->content[l];
    s.insert(display->cursor.col, toPaste);
  }
}

void yyCmd::manageClipboard() {
  display->copyLine = true;
  string &s = display->content[display->cursor.line];
  if (s.size() > 0) display->addClipboard(s);
}

void ywCmd::manageClipboard() {
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
  display->addClipboard(s.substr(c, endIndex - c));
}

void yiwCmd::manageClipboard() {
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
  display->addClipboard(s.substr(startIndex, endIndex - startIndex));
}

void yawCmd::manageClipboard() {
  string s = display->content[display->cursor.line];
  size_t &c = display->cursor.col;
  size_t startIndex = c, endIndex = c;
  string toCopy;
  if (s[c] == ' ') {
    while (startIndex > 0 && s[startIndex - 1] == ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] == ' ') endIndex++;
    toCopy = s.substr(startIndex, endIndex - startIndex);
  } else {
    while (startIndex > 0 && s[startIndex - 1] != ' ') startIndex--;
    while (endIndex < s.size() && s[endIndex] != ' ') endIndex++;
    toCopy = s.substr(startIndex, endIndex - startIndex);
    s.erase(startIndex, endIndex - startIndex);
    c = startIndex;

    endIndex = startIndex;
    while (endIndex < s.size() && s[endIndex] == ' ') endIndex++;
    toCopy += s.substr(startIndex, endIndex - startIndex);
  }
  display->addClipboard(toCopy);
}
