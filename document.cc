#include "document.h"

using namespace std;

Document::Document() {}

Document::Document(const Document &other)
    : fileName{other.fileName},
      search{other.search},
      clip{other.clip},
      saved{other.saved},
      fileExists{other.fileExists},
      exit{other.exit},
      content{other.content},
      cursor{other.cursor},
      copyLine{copyLine},
      searchForward{searchForward} {}

Document &Document::operator=(Document other) {
  fileName = other.fileName;
  search = other.search;
  clip = other.clip;
  saved = other.saved;
  fileExists = other.fileExists;
  exit = other.exit;
  content = other.content;
  cursor = other.cursor;
  copyLine = other.copyLine;
  searchForward = other.searchForward;
  return *this;
}

void Document::openDocument(ifstream &file, const string &fName) {
  fileName = fName;
  fileExists = true;
  string line;
  while (getline(file, line)) content.push_back(line);
  if (content.size() == 0) content.push_back("");
}

void Document::saveDocument() {
  ofstream out{fileName, ios::trunc};
  for (auto &line : content) {
    out << line << endl;
  }
  saved = true;
}

void Document::closeDocument() {
  if (!saved) return;
  setExit(true);
}

void Document::updateContent(WINDOW *w, WINDOW *b) {
  // init_pair(1, COLOR_WHITE, COLOR_BLUE);
  wclear(b);
  wclear(w);
  mvwprintw(b, 0, 0, commandMode ? "Command Mode" : "Insert Mode");
  if (!fileName.empty() || !saved) mvwprintw(b, 0, 14, saved ? "Changes Saved" : "Unsaved Changes");
  wrefresh(b);
  int i = 1;
  for (auto &s : content) {
    mvwprintw(w, i, 1, s.substr(0, 150).c_str());
    i++;
  }
  wmove(w, cursor.line + 1, cursor.col + 1);
  wrefresh(w);
}

void Document::setCommandMode(bool b) { commandMode = b; }

bool Document::getCommandMode() const { return commandMode; }

void Document::addClipboard(const string &s) { clip = s; }

string Document::getClipboard() const { return clip; }

string Document::getSearch() const { return search; }

void Document::setSearch(const string &s) { search = s; }

bool Document::getFileExists() const { return fileExists; }

void Document::setFileExists(bool f) { fileExists = f; }

string Document::getFileName() const { return fileName; }

void Document::setFileName(const string &s) { fileName = s; }

bool Document::getSaved() const { return saved; }

void Document::setSaved(bool s) { saved = s; }

bool Document::getExit() const { return exit; }

void Document::setExit(bool e) { exit = e; }

void Document::undoPush(Document d) { undoHistory.push(d); }

void Document::doUndo() {
  if (undoHistory.empty()) return;
  *this = undoHistory.top();
  undoHistory.pop();
}
