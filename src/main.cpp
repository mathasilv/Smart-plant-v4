#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <Fonts/FreeSerif12pt7b.h>
#define OLED_RESET 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
const int sensorUmid = A0;
const int sensorLuz = A1;

// Rosto Alegre - frame 0
const unsigned char Alegre0[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Alegre - frame 1
const unsigned char Alegre1[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};

// Rosto Alegre - frame 2
const unsigned char Alegre2[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};

// Rosto Apaixonado - frame 0
const unsigned char Apaixonado0[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xd8, 0x00, 0x0d, 0x8f, 0x80,
  0xf9, 0xfc, 0x00, 0x1f, 0xcf, 0x80, 0xf9, 0xfc, 0x00, 0x1f, 0xcf, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0x20, 0x00, 0x02, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Alegre - frame 1
const unsigned char Apaixonado1[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0xd8, 0x00, 0x0d, 0x8f, 0x80, 0xf9, 0xfc, 0x00, 0x1f, 0xcf, 0x80,
  0xfb, 0xfe, 0x00, 0x3f, 0xef, 0x80, 0xfb, 0xfe, 0x00, 0x3f, 0xef, 0x80, 0xf9, 0xfc, 0x00, 0x1f,
  0xcf, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0x20,
  0x00, 0x02, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Alegre - frame 2
const unsigned char Apaixonado2[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0xd8,
  0x00, 0x0d, 0x8f, 0x80, 0xf9, 0xfc, 0x00, 0x1f, 0xcf, 0x80, 0xfb, 0xfe, 0x00, 0x3f, 0xef, 0x80,
  0xff, 0xff, 0x00, 0x7f, 0xff, 0x80, 0xff, 0xff, 0x00, 0x7f, 0xff, 0x80, 0xfb, 0xfe, 0x00, 0x3f,
  0xef, 0x80, 0xf9, 0xfc, 0x00, 0x1f, 0xcf, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x70,
  0x00, 0x07, 0x0f, 0x80, 0xf8, 0x20, 0x00, 0x02, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0xff, 0xf0, 0x1f, 0x80, 0xfc, 0x03, 0xff, 0xe0, 0x1f, 0x80, 0xfc, 0x01, 0xff, 0xc0, 0x1f, 0x80,
  0x7e, 0x00, 0xff, 0x80, 0x3f, 0x00, 0x7f, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 0
const unsigned char Neutro0[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x00,
  0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 1
const unsigned char Neutro1[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x00,
  0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 2
const unsigned char Neutro2[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x00,
  0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 0
const unsigned char Triste0[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x3f, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0xff, 0xc0,
  0x0f, 0x80, 0xf8, 0x01, 0xff, 0xe0, 0x0f, 0x80, 0xf8, 0x03, 0xc0, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0x80, 0x70, 0x1f, 0x80, 0xfc, 0x01, 0x00, 0x20, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 1
const unsigned char Triste1[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x3f, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0xff, 0xc0,
  0x0f, 0x80, 0xf8, 0x01, 0xff, 0xe0, 0x0f, 0x80, 0xf8, 0x03, 0xc0, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0x80, 0x70, 0x1f, 0x80, 0xfc, 0x01, 0x00, 0x20, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// Rosto Neutro - frame 2
const unsigned char Triste2[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x3f, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0xff, 0xc0,
  0x0f, 0x80, 0xf8, 0x01, 0xff, 0xe0, 0x0f, 0x80, 0xf8, 0x03, 0xc0, 0xf0, 0x0f, 0x80, 0xfc, 0x03,
  0x80, 0x70, 0x1f, 0x80, 0xfc, 0x01, 0x00, 0x20, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// 'Smart plant logo', 128x64px
const unsigned char Smart_plant_logo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x84, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x03, 0x08, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x02, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xce, 0x06, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0e, 0x04, 0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x14, 0x04, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x24, 0x04, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x64, 0x03, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xc4, 0x03, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x84, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x04, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x08, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x61, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x02, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0xf9, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x70, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xde, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x91, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x10, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x18, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0xf3, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x03, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x20, 0x00, 0x01, 0x02, 0x50, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x0f, 0xe3, 0x9f, 0xc2, 0x53, 0x9e, 0xf0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc9, 0x20, 0x91, 0x03, 0x90, 0x92, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x29, 0x27, 0x91, 0x02, 0x17, 0x92, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x02, 0x29, 0x24, 0x91, 0x02, 0x14, 0x92, 0x40, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0xc9, 0x27, 0x91, 0xc2, 0x17, 0x92, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// Rosto Morto - frame único
const unsigned char Morto[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x88, 0x00, 0x08, 0x8f, 0x80,
  0xf9, 0x8c, 0x00, 0x18, 0xcf, 0x80, 0xf8, 0xd8, 0x00, 0x0d, 0x8f, 0x80, 0xf8, 0x70, 0x00, 0x07,
  0x0f, 0x80, 0xf8, 0xd8, 0x00, 0x0d, 0x8f, 0x80, 0xf9, 0x8c, 0x00, 0x18, 0xcf, 0x80, 0xf8, 0x88,
  0x00, 0x08, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0,
  0x0f, 0x80, 0xf8, 0x0f, 0xff, 0xf8, 0x0f, 0x80, 0xf8, 0x07, 0xff, 0xf0, 0x0f, 0x80, 0xfc, 0x00,
  0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// 'Dormindo0', 51x43px
const unsigned char Dormindo0[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x20, 0x01, 0xff,
  0xff, 0xff, 0xc0, 0x7c, 0xe0, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x05, 0x80, 0x07, 0xff, 0xff, 0xff,
  0xf0, 0x1d, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x33, 0xe0, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x20,
  0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x7c, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00, 0x00, 0x7f,
  0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0xfc, 0x00, 0x00,
  0x00, 0x1f, 0x80, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1f,
  0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0x00, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8,
  0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x3c, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x7e,
  0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0x80, 0x00, 0xf8, 0x00, 0x7e, 0x00, 0x0f,
  0x80, 0x00, 0xfc, 0x00, 0x3c, 0x00, 0x1f, 0x80, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00,
  0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x7f, 0x00,
  0x00, 0x00, 0x7f, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x01,
  0xfe, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00,
  0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x01,
  0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x00
};
// 'Dormindo1', 46x42px
const unsigned char Dormindo1[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x7c, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x04, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x1c, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x30, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x20, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x7c, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x3c, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00,
  0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0x80, 0xfc, 0x00,
  0x3c, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// 'Dormindo2', 41x42px
const unsigned char Dormindo2[] PROGMEM = {
  0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xff, 0xff,
  0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xf8,
  0x00, 0x0f, 0xfc, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xff, 0x00,
  0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0xfc, 0x00, 0x00, 0x00,
  0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0xf8, 0x00, 0x0f,
  0x8f, 0x80, 0xf8, 0xf8, 0x00, 0x0f, 0x8f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00,
  0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80,
  0xf8, 0x00, 0x00, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x3c, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00,
  0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x7e, 0x00, 0x0f, 0x80, 0xfc, 0x00,
  0x3c, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x1f, 0x80,
  0x7e, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x7f, 0x80, 0x00, 0x00,
  0xff, 0x00, 0x3f, 0xc0, 0x00, 0x01, 0xfe, 0x00, 0x1f, 0xf8, 0x00, 0x0f, 0xfc, 0x00, 0x0f, 0xff,
  0xff, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xe0, 0x00,
  0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00
};
// 'Escuro0', 25x8px
const unsigned char Escuro0[] PROGMEM = {
  0x70, 0x00, 0x07, 0x00, 0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x0f, 0x80,
  0x70, 0x00, 0x07, 0x00, 0x07, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xf0, 0x00
};
// 'Escuro1', 25x6px
const unsigned char Escuro1[] PROGMEM = {
  0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x0f, 0x80, 0xf8, 0x00, 0x0f, 0x80, 0x07, 0xff, 0xf0, 0x00,
  0x0f, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xf0, 0x00
};
// 'Escuro2', 25x4px
const unsigned char Escuro2[] PROGMEM = {
  0xf8, 0x00, 0x0f, 0x80, 0x07, 0xff, 0xf0, 0x00, 0x0f, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xf0, 0x00
};


void setup() {
  Serial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3c);
  pinMode(sensorUmid, INPUT);
  pinMode(sensorLuz, INPUT);
  pinMode(12, OUTPUT);

  display.clearDisplay();
      display.drawBitmap(0, 0, Smart_plant_logo, 128, 64, WHITE);
      display.display();
      delay(1000);  

  digitalWrite(12, HIGH);  
  delay(3000);
  digitalWrite(12, LOW);

}
void loop() {




while (analogRead(sensorLuz) < 860) {
    if (analogRead(sensorUmid) >= 300 && analogRead(sensorUmid) < 400) {

      display.clearDisplay();
      display.drawBitmap(44, 11, Apaixonado0, 41, 42, WHITE);
      display.display();
      delay(2000);

      display.clearDisplay();
      display.drawBitmap(44, 11, Apaixonado1, 41, 42, WHITE);
      display.display();
      delay(80);

      display.clearDisplay();
      display.drawBitmap(44, 11, Apaixonado2, 41, 42, WHITE);
      display.display();
      delay(80);


    } else if (analogRead(sensorUmid) >= 400 && analogRead(sensorUmid) < 500) {


      display.clearDisplay();
      display.drawBitmap(44, 11, Alegre0, 41, 42, WHITE);
      display.display();
      delay(2000);

      display.clearDisplay();
      display.drawBitmap(44, 11, Alegre1, 41, 42, WHITE);
      display.display();
      delay(80);

      display.clearDisplay();
      display.drawBitmap(44, 11, Alegre2, 41, 42, WHITE);
      display.display();
      delay(80);


    }

    else if (analogRead(sensorUmid) >= 500 && analogRead(sensorUmid) < 600) {


      display.clearDisplay();
      display.drawBitmap(44, 11, Neutro0, 41, 42, WHITE);
      display.display();
      delay(2000);

      display.clearDisplay();
      display.drawBitmap(44, 11, Neutro1, 41, 42, WHITE);
      display.display();
      delay(40);

      display.clearDisplay();
      display.drawBitmap(44, 11, Neutro2, 41, 42, WHITE);
      display.display();
      delay(40);


    } else if (analogRead(sensorUmid) >= 600 && analogRead(sensorUmid) < 900) {


      display.clearDisplay();
      display.drawBitmap(44, 11, Triste0, 41, 42, WHITE);
      display.display();
      delay(2000);

      display.clearDisplay();
      display.drawBitmap(44, 11, Triste1, 41, 42, WHITE);
      display.display();
      delay(40);

      display.clearDisplay();
      display.drawBitmap(44, 11, Triste2, 41, 42, WHITE);
      display.display();
      delay(40);

    }

    else if (analogRead(sensorUmid) >= 900) {

      display.clearDisplay();
      display.drawBitmap(44, 11, Morto, 41, 42, WHITE);
      display.display();
      delay(2000);
    }
  }

  if (analogRead(sensorLuz) < 950) {
    display.clearDisplay();
    display.drawBitmap(52, 32, Escuro0, 25, 8, WHITE);
    display.display();
    delay(2000);

    display.clearDisplay();
    display.drawBitmap(52, 34, Escuro1, 25, 6, WHITE);
    display.display();
    delay(40);

    display.clearDisplay();
    display.drawBitmap(52, 36, Escuro2, 25, 4, WHITE);
    display.display();
    delay(10);
  } else if (analogRead(sensorLuz) >= 950) {
    display.clearDisplay();
    display.drawBitmap(44, 11, Dormindo2, 41, 42, WHITE);
    display.display();
    delay(2000);

    display.clearDisplay();
    display.drawBitmap(44, 11, Dormindo1, 46, 42, WHITE);
    display.display();
    delay(1000);

    display.clearDisplay();
    display.drawBitmap(44, 10, Dormindo0, 51, 43, WHITE);
    display.display();
    delay(1000);
  }
}
  
  