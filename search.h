#include "command.h"

class Search : public Command {
 public:
  Search(Document *doc);
  void executeCmd() override;
  virtual void manageSearch() = 0;
};

class Slash : public Search {
  string pattern;

 public:
  Slash(Document *doc, const string &pattern);
  void manageSearch() override;
};

class Question : public Search {
  string pattern;

 public:
  Question(Document *doc, const string &pattern);
  void manageSearch() override;
};

class nCmd : public Search {
 public:
  nCmd(Document *doc) : Search(doc) {}
  void manageSearch() override;
};

class NCmd : public Search {
 public:
  NCmd(Document *doc) : Search(doc) {}
  void manageSearch() override;
};
