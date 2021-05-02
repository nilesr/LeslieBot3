#include <LiquidCrystal_I2C.h>
#include <cstdint>
#include "organize.h"
#include "smashers.h"
#include "assets/logos.h"
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
bool debug = true;

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  //lcd.cursor();
  //lcd.blink();

  pinMode(D8, INPUT);
  pinMode(D7, INPUT);
  // doesn't work right now for some reason
  debug = digitalRead(D7) && digitalRead(D8);


  initLogos();
  loadLogo(SMASH);

  if (!debug) {
    // TODO: Shuffle trivia    
    message = strdup("Welcome to LeslieBot 3");
  } else {
    message = strdup("Welcome to LeslieBot 3 (Debug Mode)");    
  }
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
    printMessage(message);
  }
}


void loopDebug() {
  static int dbgm = 0;
  static int f = 0;
  //static int i = 1;
  const bool smash = digitalRead(D7);
  const bool sans = digitalRead(D8);
  if (smash || sans) {
    dbgm = 1;
    free(message);
    message = strdup("The quick brown fox jumps over the lazy dog.");
    printMessage(message);
  }
  if (millis() - lastUpdated > 750) {
    lastUpdated = millis();
    loadLogo((franchize_t)(f++ % N_FRANCHIZE));
    if (dbgm) {
      char* nmsg = nrprintf("%s %s", message, "four");
      free(message);
      message = nmsg;
    }
    printMessage(message);
  }
}
