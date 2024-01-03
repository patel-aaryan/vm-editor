#include "command.h"

class Colon : public Command {
 public:
  Colon(Document *doc);
  void executeCmd() override;
  virtual void manageColon() = 0;
};

class Colon0 : public Colon {
 public:
  Colon0(Document *doc) : Colon(doc) {}
  void manageColon() override;
};

class ColonDollar : public Colon {
 public:
  ColonDollar(Document *doc) : Colon(doc) {}
  void manageColon() override;
};

class ColonLine : public Colon {
  size_t line, length;

 public:
  ColonLine(Document *doc, size_t line, size_t length)
      : Colon(doc), line{line}, length{length} {}
  void manageColon() override;
};

class ColonW : public Colon {
  string fileName = "";

 public:
  ColonW(Document *doc) : Colon(doc) {}
  ColonW(Document *doc, const string &fileName) : Colon(doc), fileName{fileName} {}
  void manageColon() override;
};

class ColonR : public Colon {
  string fileName;

 public:
  ColonR(Document *doc, const string &fileName) : Colon(doc), fileName{fileName} {}
  void manageColon() override;
};

class ColonQ : public Colon {
 public:
  ColonQ(Document *doc) : Colon(doc) {}
  void manageColon() override;
};

class ColonWQ : public Colon {
  string fileName = "";

 public:
  ColonWQ(Document *doc) : Colon(doc) {}
  ColonWQ(Document *doc, const string &fileName) : Colon(doc), fileName{fileName} {}
  void manageColon() override;
};

class ColonQForce : public Colon {
 public:
  ColonQForce(Document *doc) : Colon(doc) {}
  void manageColon() override;
};
