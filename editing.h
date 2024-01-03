#include "command.h"

// Abstract Editing Class
class Editing : public Command {
 public:
  Editing(Document *doc);
  void executeCmd() override;
  virtual void manageEditing() = 0;
};

// ABSTRACT DELETE CLASS
class Delete : public Editing {
 public:
  Delete(Document *doc) : Editing(doc) {}
  void manageEditing() override;
  virtual void executeDelete() = 0;
};

// Delete Subclasses
class sCmd : public Delete {
 public:
  sCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class ddCmd : public Delete {
 public:
  ddCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class ccCmd : public Delete {
 public:
  ccCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class cDollar : public Delete {
 public:
  cDollar(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class dwCmd : public Delete {
 public:
  dwCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class diwCmd : public Delete {
 public:
  diwCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class dawCmd : public Delete {
 public:
  dawCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class dhCmd : public Delete {
 public:
  dhCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class dlCmd : public Delete {
 public:
  dlCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class djCmd : public Delete {
 public:
  djCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class dkCmd : public Delete {
 public:
  dkCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class cjCmd : public Delete {
 public:
  cjCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

class ckCmd : public Delete {
 public:
  ckCmd(Document *doc) : Delete(doc) {}
  void executeDelete() override;
};

// ABSTRACT UPDATE CLASS
class Update : public Editing {
 public:
  Update(Document *doc) : Editing(doc) {}
  void manageEditing() override;
  virtual void executeUpdate() = 0;
};

// Update Subclasses
class oCmd : public Update {
 public:
  oCmd(Document *doc) : Update(doc) {}
  void executeUpdate() override;
};

class OCmd : public Update {
 public:
  OCmd(Document *doc) : Update(doc) {}
  void executeUpdate() override;
};

class JCmd : public Update {
 public:
  JCmd(Document *doc) : Update(doc) {}
  void executeUpdate() override;
};

class rCmd : public Update {
  char c;

 public:
  rCmd(Document *doc, char c) : Update(doc), c{c} {}
  void executeUpdate() override;
};
