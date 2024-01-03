#include "command.h"

class Clipboard : public Command {
 public:
  Clipboard(Document *doc, bool undo);
  void executeCmd() override;
  virtual void manageClipboard() = 0;
};

class xCmd : public Clipboard {
 public:
  xCmd(Document *doc) : Clipboard(doc, false) {}
  void manageClipboard() override;
};

class XCmd : public Clipboard {
 public:
  XCmd(Document *doc) : Clipboard(doc, false) {}
  void manageClipboard() override;
};

class pCmd : public Clipboard {
 public:
  pCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};

class PCmd : public Clipboard {
 public:
  PCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};

class yyCmd : public Clipboard {
 public:
  yyCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};

class ywCmd : public Clipboard {
 public:
  ywCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};

class yiwCmd : public Clipboard {
 public:
  yiwCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};

class yawCmd : public Clipboard {
 public:
  yawCmd(Document *doc) : Clipboard(doc, true) {}
  void manageClipboard() override;
};
