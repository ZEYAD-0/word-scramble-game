#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <format>
#include <fstream>
using namespace std;

namespace fs = filesystem;

void showGameMenu() {
  string menu = R"(
  === Word Scramble ===
1. Easy Level
2. Medium Level
3. Hard Level
4. High Scores
5. Rules
6. Back )";

  cout << menu;
}

bool saveExists(const string &name) {
  return fs::is_regular_file(fs::path("saves") / (name + ".json"));
}

string getValidName() {
  string name;
  while (true) {
    cout << "Enter name: ";
    cin >> name;
    if (all_of(name.begin(), name.end(), ::isalnum))
      return name;
    cout << "Letters and numbers only.\n";
  }
}

bool createSaveFile(const string &name) {
  fs::create_directories("saves");

  ofstream file("saves/" + name + ".json");
  if (!file)
    return false;

  string content = format(R"({{
  "name": "{}",
  "easySolved": {},
  "mediumSolved": {},
  "hardSolved": {}
}})",
  name, 0, 0, 0);

  file << content;
  return true;
}

void runGame() {
  string name = getValidName();
  if (not saveExists(name))
  {
    if (createSaveFile(name))
    {
      cout << "Hi " << name << '\n';
    }
  }
  else
  {
    cout << "Welcome back, " << name << '\n';
  }
  showGameMenu();
}

int main() {
  runGame();
}