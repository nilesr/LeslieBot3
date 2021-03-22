#include <LiquidCrystal_I2C.h>
#include <cstdint>
#include "organize.h"


LiquidCrystal_I2C lcd(0x27,20,4);

uint8_t ball_1[8]  = {0b00000, 0b00000, 0b00100, 0b01100, 0b01100, 0b11100, 0b11100, 0b11100};
uint8_t ball_2[8]  = {0b01111, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111};
uint8_t ball_3[8]  = {0b00000, 0b11000, 0b11100, 0b11110, 0b11110, 0b11111, 0b11111, 0b11111};
uint8_t ball_4[8]  = {0b11100, 0b00000, 0b00000, 0b01100, 0b01100, 0b00100, 0b00000, 0b00000};
uint8_t ball_5[8]  = {0b01111, 0b00000, 0b00000, 0b01111, 0b01111, 0b01111, 0b01111, 0b01111};
uint8_t ball_6[8]  = {0b11111, 0b00000, 0b00000, 0b11110, 0b11110, 0b11100, 0b11000, 0b00000};

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


void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  //lcd.cursor();
  //lcd.blink();
  
  
  lcd.createChar(0, ball_1);
  lcd.createChar(1, ball_2);
  lcd.createChar(2, ball_3);
  lcd.createChar(3, ball_4);
  lcd.createChar(4, ball_5);
  lcd.createChar(5, ball_6);

  printMessage("Hello, world! And some more text to force it to wrap");

  
}


void loop() {
  static std::string message = "Hello";
  delay(1000);
  message += " a";
  char* cstr = strdup(message.c_str());
  printMessage(cstr);
  free(cstr);
}
