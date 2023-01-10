#include <avr/pgmspace.h>

// ----------------------------------------------------------------------------

/* Standard ASCII 6x8 font */
const uint8_t ssd1306xled_font6x8_digits_and_decimal [] PROGMEM = {
  0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
  0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
  0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
  0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
  0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
  0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
  0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
  0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
  0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
  0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
  0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
  0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
};

// ----------------------------------------------------------------------------

const DCfont TinyOLED4kfont6x8Decimal = {
  (uint8_t *)ssd1306xled_font6x8_digits_and_decimal,
  6, // character width in pixels
  1, // character height in pages (8 pixels)
  46,57 // ASCII extents
  };

// for backwards compatibility
#define FONT6X8DECIMAL (&TinyOLED4kfont6x8Decimal)