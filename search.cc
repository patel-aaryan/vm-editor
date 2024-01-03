#include "search.h"

Search::Search(Document *doc) : Command(CommandType::Search, false, doc) {}

void Search::executeCmd() { manageSearch(); }

Slash::Slash(Document *doc, const string &pattern)
    : Search(doc), pattern{pattern} {
  display->setSearch(pattern);
  display->searchForward = true;
}

void Slash::manageSearch() {
  string &s = display->content[display->cursor.line];
  size_t pos = s.find(pattern, display->cursor.col);
  if (pos != string::npos) display->cursor.col = pos;
}

Question::Question(Document *doc, const string &pattern)
    : Search(doc), pattern{pattern} {
  display->setSearch(pattern);
  display->searchForward = false;
}

void Question::manageSearch() {
  size_t &c = display->cursor.col;
  string s = display->content[display->cursor.line].substr(0, c);
  size_t pos = s.find(pattern);
  if (pos != string::npos) {
    size_t newPos = pos;
    while (newPos != string::npos) {
      pos = newPos;
      newPos = s.find(display->getSearch(), newPos + 1);
    }
    c = pos;
  }
}

void nCmd::manageSearch() {
  if (display->getSearch().empty()) return;
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string s = display->content[l];

  bool done = false;
  size_t pos = 0;
  if (display->searchForward) {
    pos = s.find(display->getSearch(), c + 1);
    if (pos != string::npos) {
      c = pos;
      return;
    }

    if (l == display->content.size() - 1) return;
    l++;

    while (!done) {
      s = display->content[l];
      pos = s.find(display->getSearch());

      if (pos != string::npos) {
        c = pos;
        done = true;
      } else {
        if (l == display->content.size() - 1) return;
        l++;
      }
    }
  } else {
    s = s.substr(0, c);
    pos = s.find(display->getSearch());
    if (pos != string::npos) {
      size_t newPos = pos;
      while (newPos != string::npos) {
        pos = newPos;
        newPos = s.find(display->getSearch(), newPos + 1);
      }
      c = pos;
      return;
    }

    if (l == 0) return;
    l--;

    while (!done) {
      s = display->content[l];
      pos = s.find(display->getSearch());

      if (pos != string::npos) {
        size_t newPos = pos;
        while (newPos != string::npos) {
          pos = newPos;
          newPos = s.find(display->getSearch(), newPos + 1);
        }
        c = pos;
        done = true;
      } else {
        if (l == 0) return;
        l--;
      }
    }
  }
}

void NCmd::manageSearch() {
  if (display->getSearch().empty()) return;
  size_t &l = display->cursor.line;
  size_t &c = display->cursor.col;
  string s = display->content[l];

  bool done = false;
  size_t pos = 0;
  if (!display->searchForward) {
    pos = s.find(display->getSearch(), c + 1);
    if (pos != string::npos) {
      c = pos;
      return;
    }

    if (l == display->content.size() - 1) return;
    l++;

    while (!done) {
      s = display->content[l];
      pos = s.find(display->getSearch());

      if (pos != string::npos) {
        c = pos;
        done = true;
      } else {
        if (l == display->content.size() - 1) return;
        l++;
      }
    }
  } else {
    s = s.substr(0, c);
    pos = s.find(display->getSearch());
    if (pos != string::npos) {
      size_t newPos = pos;
      while (newPos != string::npos) {
        pos = newPos;
        newPos = s.find(display->getSearch(), newPos + 1);
      }
      c = pos;
      return;
    }

    if (l == 0) return;
    l--;

    while (!done) {
      s = display->content[l];
      pos = s.find(display->getSearch());

      if (pos != string::npos) {
        size_t newPos = pos;
        while (newPos != string::npos) {
          pos = newPos;
          newPos = s.find(display->getSearch(), newPos + 1);
        }
        c = pos;
        done = true;
      } else {
        if (l == 0) return;
        l--;
      }
    }
  }
}
