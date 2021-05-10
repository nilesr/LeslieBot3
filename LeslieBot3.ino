#include <LiquidCrystal_I2C.h>
#include <cstdint>
#include "organize.h"
#include "smashers.h"
#include "assets/logos.h"
#include "trivia/trivia.h"
#define DEFINE_SELECTORS 1
#include "random.h"

void loopDebug();

LiquidCrystal_I2C lcd(0x27,20,4);

void drawChar(char chr) {
  lcd.print(chr);
}

void drawWord(const char* word) {
  lcd.print(word);
}

void setCursor(int x, int y) {
  lcd.setCursor(x, y);
}

int serial(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  char buf[1024];
  vsnprintf(buf, 1024, fmt, args);
  va_end(args);
  Serial.printf("%s", buf);
}

void loadLogo(franchize_t franchize) {
  for (int i = 0; i < 6; i++) {
    lcd.createChar(i, logos[franchize][i]);
  }
}

int random() {
  int r = RANDOM_REG32;
  if (r < 0) {
    r = -r;
  }
  return r;
}

char* message;
bool on_startup_screen = true;
long lastUpdated;
bool debug = false;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  //lcd.cursor();
  //lcd.blink();

  pinMode(D8, INPUT);
  pinMode(D7, INPUT);


  initLogos();
  loadLogo(SMASH);

  message = strdup("Welcome to LeslieBot 3");
  printMessage(message);

  lastUpdated = millis();

  
}

void loop() {
  if (debug) {
    loopDebug();
    return;
  }
  const bool smash = digitalRead(D7);
  const bool sans = digitalRead(D8);
  if (smash && sans) {
    debug = true;
    on_startup_screen = true;
    free(message);
    message = strdup("Welcome to LeslieBot 3 (Debug mode)");
    printMessage(message);
    while (digitalRead(D7) || digitalRead(D8));
    return;
  }
  if (smash || sans) {
    on_startup_screen = false;
    if (smash) {
      free(message);
      message = random_challenge();
    } else {
      free(message);
      message = random_trivia();
    }
    printMessage(message);
  }
  if (on_startup_screen && millis() - lastUpdated > 1000) {
    lastUpdated = millis();
    static int f = 1;
    loadLogo((franchize_t)(f++ % N_FRANCHIZE));
    if (f % N_FRANCHIZE == 0) {
      switch ((f / N_FRANCHIZE) % 4) {
        case 0:
          free(message);
          message = strdup("Welcome to LeslieBot 3");
          break;
        case 1:
          free(message);
          message = nrprintf("Welcome to LeslieBot 3. I'm aware of %d smash characters", N_SMASHERS);
          break;
        case 2:
          free(message);
          message = nrprintf("Welcome to LeslieBot 3. I know %d trivia messages", N_TRIVIA);
          break;
        case 3:
          free(message);
          message = nrprintf("Welcome to LeslieBot 3. I have %d possible randomizers", N_SELECTOR);
          break;
      }
    }
    printMessage(message);
  }
}


void loopDebug() {
  static int dbgm = 0;
  static int f = 0;
  static int i = 1;
  const bool smash = digitalRead(D7);
  const bool sans = digitalRead(D8);
  if (smash || sans) {
    dbgm = 1;
  }
  if (millis() - lastUpdated > 750) {
    lastUpdated = millis();
    loadLogo((franchize_t)(f++ % N_FRANCHIZE));
    if (dbgm == 1) {
      i++;
      if (i % 20 == 0) {
        free(message);
        message = strdup("Welcome to LeslieBot 3 (Debug mode)");
      }
      static const char* const dls[5] = {
        "four", "three", "two", "a", "abcdefgh"
      };
      char* nmsg = nrprintf("%s %s", message, dls[(i / 20) % 5]);
      free(message);
      message = nmsg;
    }
    printMessage(message);
  }
}
