#include <LiquidCrystal_I2C.h>
#include <cstdint>
#include "organize.h"
#include "smashers.h"
#include "assets/logos.h"


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


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  //lcd.cursor();
  //lcd.blink();

  initLogos();
  loadLogo(SMASH);

  printMessage("Hello, world! And some more text to force it to wrap");

  
}


void loop() {
  static int f = 1;
  loadLogo((franchize_t)(f++ % N_FRANCHIZE));
  printMessage("Hello, world! And some more text to force it to wrap");
  delay(1000);
}
