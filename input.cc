#include "input.h"

#include <iostream>
#include <string>

#include "clipboard.h"
#include "colon.h"
#include "editing.h"
#include "insert.h"
#include "miscCommands.h"
#include "navigation.h"
#include "search.h"
using namespace std;

const string navigationCmds[] = {"h", "j", "k", "l", "$", "^", "0", "b", "w", "f", "F", "%"};
const string switchToInsert[] = {"a", "i", "A", "I"};
const string deleteCmds[] = {"S", "s", "c", "d"};
const string updateCmds[] = {"o", "O", "J", "r"};
const string clipboardCmds[] = {"x", "X", "p", "P", "y"};
const string searchCmds[] = {"/", "?", "n", "N"};

Input::Input(char c) { inp += c; }
Input::Input(const string &inp) : inp{inp} {}

unique_ptr<Command> Input::convertNavigation(Document *doc) {
  if (inp == "h") {
    return make_unique<hCmd>(doc);
  } else if (inp == "j") {
    return make_unique<jCmd>(doc);
  } else if (inp == "k") {
    return make_unique<kCmd>(doc);
  } else if (inp == "l") {
    return make_unique<lCmd>(doc);
  } else if (inp == "$") {
    return make_unique<Dollar>(doc);
  } else if (inp == "^" || inp == "0") {
    return make_unique<Chevron>(doc);
  } else if (inp == "b") {
    return make_unique<bCmd>(doc);
  } else if (inp == "w") {
    return make_unique<wCmd>(doc);
  } else if (inp == "f") {
    return make_unique<fCmd>(doc, getch());
  } else if (inp == "F") {
    return make_unique<FCmd>(doc, getch());
  } else if (inp == "%") {
    return make_unique<Percent>(doc);
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertNavigationInsert(Document *doc) {
  doc->setCommandMode(false);
  if (inp == "a") {
    return make_unique<aCmd>(doc);
  } else if (inp == "i") {
    return make_unique<iCmd>(doc);
  } else if (inp == "A") {
    return make_unique<Dollar>(doc);
  } else if (inp == "I") {
    return make_unique<Chevron>(doc);
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertDelete(Document *doc, WINDOW *win) {
  if (inp == "S") {
    doc->setCommandMode(false);
    return make_unique<ddCmd>(doc);
  } else if (inp == "s") {
    return make_unique<sCmd>(doc);
  } else if (inp == "d") {
    mvwprintw(win, 0, 100, inp.c_str());
    wrefresh(win);
    inp += getch();
    if (inp == "dd") {
      return make_unique<ddCmd>(doc);
    } else if (inp == "dw") {
      return make_unique<dwCmd>(doc);
    } else if (inp == "dh") {
      return make_unique<dhCmd>(doc);
    } else if (inp == "dj") {
      return make_unique<djCmd>(doc);
    } else if (inp == "dk") {
      return make_unique<dkCmd>(doc);
    } else if (inp == "dl") {
      return make_unique<dlCmd>(doc);
    } else {
      mvwprintw(win, 0, 100, inp.c_str());
      wrefresh(win);
      inp += getch();
      if (inp == "diw") {
        return make_unique<diwCmd>(doc);
      } else if (inp == "daw") {
        return make_unique<dawCmd>(doc);
      }
    }
  } else if (inp == "c") {
    mvwprintw(win, 0, 100, inp.c_str());
    wrefresh(win);
    inp += getch();
    if (inp == "cc") {
      return make_unique<ccCmd>(doc);
    } else if (inp == "c$") {
      return make_unique<cDollar>(doc);
    } else if (inp == "cw") {
      doc->setCommandMode(false);
      return make_unique<dwCmd>(doc);
    } else if (inp == "ch") {
      doc->setCommandMode(false);
      return make_unique<dhCmd>(doc);
    } else if (inp == "cj") {
      return make_unique<cjCmd>(doc);
    } else if (inp == "ck") {
      return make_unique<ckCmd>(doc);
    } else if (inp == "cl") {
      doc->setCommandMode(false);
      return make_unique<dlCmd>(doc);
    } else {
      mvwprintw(win, 0, 100, inp.c_str());
      wrefresh(win);
      inp += getch();
      doc->setCommandMode(false);
      if (inp == "ciw") return make_unique<diwCmd>(doc);
    }
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertUpdate(Document *doc) {
  if (inp == "O") {
    return make_unique<OCmd>(doc);
  } else if (inp == "o") {
    return make_unique<oCmd>(doc);
  } else if (inp == "J") {
    return make_unique<JCmd>(doc);
  } else if (inp == "r") {
    return make_unique<rCmd>(doc, getch());
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertClipboard(Document *doc, WINDOW *win) {
  if (inp == "x") {
    return make_unique<xCmd>(doc);
  } else if (inp == "X") {
    return make_unique<XCmd>(doc);
  } else if (inp == "p") {
    return make_unique<pCmd>(doc);
  } else if (inp == "P") {
    return make_unique<PCmd>(doc);
  } else if (inp == "y") {
    mvwprintw(win, 0, 100, inp.c_str());
    wrefresh(win);
    inp += getch();
    if (inp == "yy") {
      return make_unique<yyCmd>(doc);
    } else if (inp == "yw") {
      return make_unique<ywCmd>(doc);
    } else {
      mvwprintw(win, 0, 100, inp.c_str());
      wrefresh(win);
      inp += getch();
      if (inp == "yiw") {
        return make_unique<yiwCmd>(doc);
      } else if (inp == "yaw") {
        return make_unique<yawCmd>(doc);
      }
    }
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertColon(Document *doc, WINDOW *win) {
  int ch;
  mvwprintw(win, 0, 100, inp.c_str());
  wrefresh(win);
  while ((ch = getch()) != '\n') {
    inp += ch;
    mvwprintw(win, 0, 100, inp.c_str());
    wrefresh(win);
  }
  mvwprintw(win, 0, 100, inp.c_str());
  wrefresh(win);

  if (inp == ":0") {
    return make_unique<Colon0>(doc);
  } else if (inp == ":$") {
    return make_unique<ColonDollar>(doc);
  } else if (inp == ":w") {
    return make_unique<ColonW>(doc);
  } else if (inp.substr(0, 3) == ":w ") {
    return make_unique<ColonW>(doc, inp.substr(3));
  } else if (inp == ":q") {
    return make_unique<ColonQ>(doc);
  } else if (inp == ":wq") {
    return make_unique<ColonWQ>(doc);
  } else if (inp.substr(0, 4) == ":wq ") {
    return make_unique<ColonWQ>(doc, inp.substr(4));
  } else if (inp == ":q!") {
    return make_unique<ColonQForce>(doc);
  } else if (inp.substr(0, 3) == ":r ") {
    return make_unique<ColonR>(doc, inp.substr(3));
  } else {
    string isLineNumber = inp.substr(1);
    bool isNumber = true;
    size_t num = 0;
    for (auto &i : isLineNumber) {
      if (i < '0' || i > '9') {
        isNumber = false;
        break;
      }
      num = num * 10 + (i - '0');
    }
    if (isNumber) return make_unique<ColonLine>(doc, num - 1, doc->content.size() - 1);
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convertSearch(Document *doc, WINDOW *win) {
  if (inp == "n") {
    return make_unique<nCmd>(doc);
  } else if (inp == "N") {
    return make_unique<NCmd>(doc);
  } else {
    int ch;
    while ((ch = getch()) != '\n') {
      mvwprintw(win, 0, 100, inp.c_str());
      wrefresh(win);
      inp += ch;
    }
    mvwprintw(win, 0, 100, inp.c_str());
    wrefresh(win);
    if (inp[0] == '/') {
      string asdf = inp.substr(1);
      return make_unique<Slash>(doc, inp.substr(1));
    } else if (inp[0] == '?') {
      return make_unique<Question>(doc, inp.substr(1));
    }
  }
  return make_unique<InvalidCommand>(doc);
}

unique_ptr<Command> Input::convert(Document *doc, WINDOW *win) {
  if (doc->getCommandMode()) {
    for (auto &s : navigationCmds) {
      if (inp == s) return convertNavigation(doc);
    }
    for (auto &s : switchToInsert) {
      if (inp == s) return convertNavigationInsert(doc);
    }
    for (auto &s : deleteCmds) {
      if (inp == s) return convertDelete(doc, win);
    }
    for (auto &s : updateCmds) {
      if (inp == s) return convertUpdate(doc);
    }
    for (auto &s : clipboardCmds) {
      if (inp == s) return convertClipboard(doc, win);
    }
    for (auto &s : searchCmds) {
      if (inp == s) return convertSearch(doc, win);
    }

    if (inp == ":") {
      return convertColon(doc, win);
    } else if (inp == "u") {
      return make_unique<Undo>(doc);
    }
  } else {
    if (inp == "enter") {
      return make_unique<Enter>(doc);
    } else if (inp == "escape") {
      return make_unique<Escape>(doc);
    } else if (inp == "backspace") {
      return make_unique<Backspace>(doc);
    } else {
      return make_unique<Insert>(inp, doc);
    }
  }
  return make_unique<InvalidCommand>(doc);
}
