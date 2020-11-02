#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

string getNewFileName(string fileName, string suffix);

int getWordsInString(string str, string words[]) {
  char c;
  char word[200];
  int wi = 0;  // Word iterator
  int wsi = 0; // Words iterator
  int n = 0;   // Number of words found
  for (int i = 0; i < str.length() + 1; i++) {
    c = str[i];
    if (c == ' ' || c == ';' || c == '\0') {
      if (wi > 0) {
        word[wi] = '\0';
        words[wsi++] = word;
        n++;
      }
      wi = 0;
      continue;
    }
    word[wi++] = c;
  }

  return n;
}

bool stringBeginWith(string phrase, string str) {
  string wordsP[200];
  string wordsS[200];
  int wpLength = getWordsInString(phrase, wordsP);
  int wsLength = getWordsInString(str, wordsS);

  for (int i = 0; i < wpLength; i++) {
    if (wordsP[i] != wordsS[i]) {
      return false;
    }
  }
  return true;
}

string findFileNameInPath(string path) {
  char c;
  for (int i = path.length(); i > 0; i--) {
    c = path[i];
    if (c == '/') {
      return path.substr(i + 1, path.length() - 1 - i - 1);
    }
  }

  throw(path);
  return path;
}

string getNewModulePath(string path, string suffix) {
  string fileName;
  char c;
  int i = path.length();
  for (; i > 0; i--) {
    c = path[i];
    if (c == '/') {
      fileName = path.substr(i + 1, path.length() - 1 - i - 1);
      break;
    }
  }
  if (i == 0 || path[0] != '\'' || path[path.length() - 1] != '\'') {
    throw("Invalid path!");
  }

  string newFileName = getNewFileName(fileName, suffix);

  return path.substr(0, i + 1) + newFileName + "'";
}

int main(int argc, char *argv[]) {
  // if (argc == 1) {
  //   cout << "Oops! You didn't give me a file to work on." << endl;
  // } else {

  // }

  cout << "Let's go!" << endl;

  string inFileName = "testfile.js";
  string suffix = "_njs";
  string outFileName = getNewFileName(inFileName, suffix);

  ifstream readFile(inFileName);
  ofstream writeFile(outFileName);

  string importPhrase = "import * as";
  string exportPhrase = "export {";
  string line;

  string words[20];
  int length;
  string moduleName;
  string modulePath;
  string newModulePath;
  while (getline(readFile, line)) {
    if (stringBeginWith(importPhrase, line)) {
      length = getWordsInString(line, words);
      if (length < 5) {
        // This shouldn't happen
        cout << "ERROR!!!" << endl;
        exit(1);
      }
      moduleName = words[3];
      modulePath = words[5];
      newModulePath = getNewModulePath(modulePath, suffix);
      line = "const " + moduleName + " = require(" + newModulePath + ");";
    } else {
      if (stringBeginWith(exportPhrase, line)) {
        length = getWordsInString(line, words);
        if (length < 2) {
          // This shouldn't happen
          cout << "ERROR!!!" << endl;
          exit(1);
        }
        line = "module.exports = {";
      }
    }

    writeFile << line << endl;
  }

  readFile.close();
  writeFile.close();

  ////////////////TEST//////////
  // string str1 = "hej";
  // string str2 = "hej";

  // if (str1 == str2) {
  //   cout << "lika" << endl;
  // } else {
  //   cout << "olika" << endl;
  // }

  // string w1 = "w1";
  // string w2 = "w2";
  // string w3 = "w3";
  // // string words[10] = {w1, w2, w3};
  // int i1 = 1;
  // int i2 = 2;
  // int i3 = 3;
  // int ints[10] = {i1, i2, i3};

  // for (int i = 0; i < 3; i++) {
  // cout << words[i] << endl;
  // }

  // string newFileName;
  // getNewFileName("apan.js", "_mod", newFileName);
  // cout << newFileName << endl;

  return 0;
}

string getNewFileName(string fileName, string suffix) {
  string fileExtension;
  string fileNameNoExtension;
  char c;
  int position = fileName.length();
  for (int i = fileName.length(); i > 0; i--) {
    c = fileName[i];
    if (c == '.') {
      position = i;
      break;
    }
  }
  fileExtension = fileName.substr(position);
  fileNameNoExtension = fileName.substr(0, position);
  return fileNameNoExtension + suffix + fileExtension;
}