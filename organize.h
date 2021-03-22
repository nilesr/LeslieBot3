#include <vector>
#include <cstring>
#include <algorithm>

const int MAXL = 20*4;

void drawChar(char chr);

void drawWord(const char* word);

void setCursor(int x, int y);

bool canFitWithWrap(const std::vector<char*>& words, bool withLogo);

void drawWithWrap(const std::vector<char*>& words, bool withLogo);

void drawLogo();

bool canDrawNoWrap(int raw_chars, int words);

void drawNoWrap(const std::vector<char*>& words);

void drawNoWhitespace(const std::vector<char*>& words);

void printMessage(char* string);

int serial(const char* fmt, ...);
