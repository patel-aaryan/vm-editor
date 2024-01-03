#include "colon.h"

#include <fstream>
#include <iostream>

// Navigation Class
Colon::Colon(Document *doc) : Command(CommandType::Colon, false, doc) {}
void Colon::executeCmd() { manageColon(); }

// Subclasses
void Colon0::manageColon() {
  display->cursor.line = 0;
  display->cursor.col = 0;
}

void ColonDollar::manageColon() {
  display->cursor.line = display->content.size() - 1;
  display->cursor.col = 0;
}

void ColonLine::manageColon() {
  display->cursor.line = line > length ? length : line;
  display->cursor.col = 0;
}

void ColonW::manageColon() {
  if (fileName.empty()) {
    if (display->getFileExists()) display->saveDocument();
  } else {
    Document toSave = *display;
    toSave.setFileName(fileName);
    toSave.saveDocument();
    display->setFileName(fileName);
    display->setFileExists(true);
    display->setSaved(true);
  }
}

void ColonR::manageColon() {
  size_t l = display->cursor.line;
  ifstream f{fileName};
  string line;
  while (getline(f, line)) {
    display->content.insert(display->content.begin() + ++l, line);
  }
  display->cursor.line++;
  display->cursor.col = 0;
}

void ColonQ::manageColon() {
  if (!display->getSaved()) return;
  display->closeDocument();
}

void ColonWQ::manageColon() {
  if (fileName.empty()) {
    if (display->getFileExists()) {
      display->saveDocument();
      display->closeDocument();
    }
  } else {
    Document toSave = *display;
    toSave.setFileName(fileName);
    toSave.saveDocument();
    display->setFileName(fileName);
    display->setFileExists(true);
    display->setSaved(true);
    display->closeDocument();
  }
}

void ColonQForce::manageColon() { display->setExit(true); }
