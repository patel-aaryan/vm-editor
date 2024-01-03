
#include "command.h"

class Navigation : public Command {
 protected:
  size_t &docLine, &docCol;

 public:
  Navigation(Document *doc);
  void executeCmd() override;
  virtual void manageNavigation() = 0;
};

class hCmd : public Navigation {
 public:
  hCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class jCmd : public Navigation {
 public:
  jCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class kCmd : public Navigation {
 public:
  kCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class lCmd : public Navigation {
 public:
  lCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class aCmd : public Navigation {
 public:
  aCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class iCmd : public Navigation {
 public:
  iCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override {}
};

class Dollar : public Navigation {
 public:
  Dollar(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class Chevron : public Navigation {
 public:
  Chevron(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class bCmd : public Navigation {
 public:
  bCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class wCmd : public Navigation {
 public:
  wCmd(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};

class fCmd : public Navigation {
  char ch;

 public:
  fCmd(Document *doc, char ch) : Navigation(doc), ch{ch} {}
  void manageNavigation() override;
};

class FCmd : public Navigation {
  char ch;

 public:
  FCmd(Document *doc, char ch) : Navigation(doc), ch{ch} {}
  void manageNavigation() override;
};

class Percent : public Navigation {
  char bracket = ' ';

 public:
  Percent(Document *doc) : Navigation(doc) {}
  void manageNavigation() override;
};
