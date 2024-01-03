#include <ncurses.h>

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

#include "command.h"
#include "document.h"
#include "input.h"

using namespace std;

const int BAR_HEIGHT = 1;
const int HEIGHT = 50;
const int WIDTH = 150;
const int KEY_ESCAPE = 27;
const int NEW_LINE = '\n';

int main(int argc, char const* argv[]) {
  Document doc;
  if (argc > 1) {
    ifstream f{argv[1]};
    doc.openDocument(f, argv[1]);
  } else {
    doc.content.push_back("");
  }

  initscr();
  keypad(stdscr, TRUE);
  noecho();
  WINDOW* bar = newwin(BAR_HEIGHT, WIDTH, 0, 0);
  curs_set(0);
  WINDOW* win = newwin(HEIGHT, WIDTH, 1, 0);
  curs_set(1);
  refresh();
  doc.updateContent(win, bar);

  while (!doc.getExit()) {
    int ch = getch();
    Input inp;
    size_t lineLength;
    switch (ch) {
      case KEY_UP:
        if (doc.cursor.line > 0) doc.cursor.line--;
        lineLength = doc.content[doc.cursor.line].size();
        if (lineLength < doc.cursor.col) doc.cursor.col = lineLength;
        break;
      case KEY_DOWN:
        if (doc.cursor.line < doc.content.size() - 1) doc.cursor.line++;
        lineLength = doc.content[doc.cursor.line].size();
        if (lineLength < doc.cursor.col) doc.cursor.col = lineLength;
        break;
      case KEY_LEFT:
        if (doc.cursor.col > 0) doc.cursor.col--;
        break;
      case KEY_RIGHT:
        if (doc.cursor.col < doc.content[doc.cursor.line].size()) doc.cursor.col++;
        break;
      default:
        switch (ch) {
          case KEY_BACKSPACE:
            inp = Input{"backspace"};
            break;
          case KEY_ESCAPE:
            inp = Input{"escape"};
            break;
          case NEW_LINE:
            inp = Input{"enter"};
            break;
          default:
            inp = Input{ch};
            break;
        }
        auto c = inp.convert(&doc, bar);
        c->manageCmd();
        break;
    }
    doc.updateContent(win, bar);
  }

  delwin(win);
  endwin();
}
