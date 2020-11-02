#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// void getNewFileName(string& fileName);
void getNewFileName(string &fileName, string &newFileName, string &suffix);

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

int main(int argc, char *argv[]) {
  // if (argc == 1) {
  //   cout << "Oops! You didn't give me a file to work on." << endl;
  // } else {

  // }

  string inFileName = "testfile.js";
  string outFileName = "testfile_nodeJs.js";

  ifstream readFile(inFileName);
  ofstream writeFile(outFileName);

  string phrase = "import * as";
  string line;
  // getline(readFile, line);

  string words[20];
  int length;
  string moduleName;
  string modulePath;
  while (getline(readFile, line)) {
    if (stringBeginWith(phrase, line)) {
      length = getWordsInString(line, words);
      if (length < 5) {
        // This shouldn't happen
        cout << "ERROR!!!" << endl;
        exit(1);
      }
      moduleName = words[3];
      modulePath = words[5];
      line = "const " + moduleName + " = require(" + modulePath + ");";
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

  return 0;
}

void getNewFileName(string &fileName, string &newFileName, string &suffix) {
  string delimiter = ".";
  int pos = fileName.find(delimiter);
  suffix = (pos != -1) ? fileName.substr(pos) : "";
  string nameExSuffix = fileName.substr(0, pos);
  newFileName = nameExSuffix + "_copy" + suffix;
  cout << newFileName << endl;
}