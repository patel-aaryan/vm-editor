#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <ncurses.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

#include "command.h"

using namespace std;

class Command;

struct Posn {
  size_t line, col;
};

class Document {
  string fileName, search, clip;
  bool commandMode = true, saved = true, fileExists = false, exit = false;
  stack<Document> undoHistory;

 public:
  Document();
  Document(const Document& other);
  Document& operator=(Document other);

  vector<string> content;
  Posn cursor = {0, 0};
  bool copyLine = false;
  bool searchForward;

  void updateContent(WINDOW* w, WINDOW* b);
  void openDocument(ifstream& file, const string& fileName);
  void saveDocument();
  void closeDocument();

  string getClipboard() const;
  void addClipboard(const string& s);

  bool getCommandMode() const;
  void setCommandMode(bool b);

  string getSearch() const;
  void setSearch(const string& s);

  bool getFileExists() const;
  void setFileExists(bool f);

  string getFileName() const;
  void setFileName(const string& s);

  bool getSaved() const;
  void setSaved(bool f);

  bool getExit() const;
  void setExit(bool e);

  void undoPush(Document d);
  void doUndo();

  ~Document() = default;
};
#endif
