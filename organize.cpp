#include <vector>
#include <cstring>
#include <algorithm>
#include "organize.h"

void drawChar(char chr);

void drawWord(const char* word);

void setCursor(int x, int y);

bool canFitWithWrap(const std::vector<char*>& words, bool withLogo) {
  int l = 0;
  int ll = 0;
  for (const auto& word : words) {
    int maxl = (withLogo && l > 1) ? 17 : 20;
    const int wl = strlen(word);
    if (ll + 1 + wl < maxl) {
      ll += 1 + wl;
    } else {
      l++;
      ll = wl;
    }
    if (l == 4) {
      return false;
    }
  }
  return true;
}

void drawWithWrap(const std::vector<char*>& words, bool withLogo) {
  int l = 0;
  int ll = 0;
  for (const auto& word : words) {
    int maxl = (withLogo && l > 1) ? 17 : 20;
    const int wl = strlen(word);
    if (ll + 1 + wl < maxl) {
      ll += 1 + wl;
      drawWord(word);
      drawChar(' ');
    } else {
      l++;
      ll = wl;
      setCursor(0, l);
      drawWord(word);
      drawChar(' ');
    }
  }
}

void drawLogo() {
  setCursor(17, 2);
  drawChar(0);
  drawChar(1);
  drawChar(2);
  setCursor(17, 3);
  drawChar(3);
  drawChar(4);
  drawChar(5);
}

bool canDrawNoWrap(int raw_chars, int words) {
  return raw_chars + (words - 1) < MAXL;
}

void drawNoWrap(const std::vector<char*>& words) {
  int l = 0;
  int ll = 0;
  for (int i = 0; i < words.size(); i++) {
    const auto& word = words[i];
    for (int c = 0; word[c]; c++) {
      drawChar(word[c]);
      ll++;
      if (ll == 20) {
	ll = 0;
	l++;
	setCursor(0, l);
      }
    }
    if (i != words.size() - 1) {
      drawChar(' ');
    }
  }
}

void drawNoWhitespace(const std::vector<char*>& words) {
  int l = 0;
  int ll = 0;
  for (int i = 0; i < words.size(); i++) {
    const auto& word = words[i];
    for (int c = 0; word[c]; c++) {
      if (c == 0) {
	drawChar(word[c] & ~32);
      } else {
	drawChar(word[c]);
      }
      ll++;
      if (ll == 20) {
	ll = 0;
	l++;
	setCursor(0, l);
      }
    }
  }
}

void clearScreen() {
  for (int l = 0; l < 4; l++) {
    setCursor(0, l);
    drawWord("                    ");
  }
}

void printMessage(char* string) {
  setCursor(0, 0);
  clearScreen();
  std::vector<char*> words{};
  int sum = 0;
  while (char* word = strtok(string, " ")) {
    string = nullptr;
    sum += strlen(word);
    words.push_back(strdup(word));
    serial("%s: %d, accumulated %d\n", word, strlen(word), words.size());
  }
  if (canFitWithWrap(words, true)) {
    drawWithWrap(words, true);
    drawLogo();
  } else if (canFitWithWrap(words, false)) {
    drawWithWrap(words, false);
  } else if (canDrawNoWrap(sum, words.size())) {
    drawNoWrap(words);
  } else if (sum < MAXL) {
    drawNoWhitespace(words);
  } else {
    drawWord("Too long! Giving up");
  }
}
