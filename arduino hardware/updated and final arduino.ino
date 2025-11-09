#include "C:/Users/kevin/Documents/Arduino/libraries/QRCode/src/qrcode.h"
#include "C:/Users/kevin/Documents/Arduino/libraries/QRCode/src/qrcode.c"

#include <U8g2lib.h>

// Initialize the display (I2C, SH1106)
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  u8g2.begin();

  // Generate QR code
  QRCode qrcode;
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, "https://verdant-baklava-218dc7.netlify.app");

  Serial.println("QR Code:");
  uint32_t dt = millis();

  // Display QR on Serial (optional)
  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      Serial.print(qrcode_getModule(&qrcode, x, y) ? "##" : "  ");
    }
    Serial.println();
  }

  Serial.print("QR Code Generation Time: ");
  Serial.println(millis() - dt);

  // Display on OLED
  u8g2.clearBuffer();
  const uint8_t scale = 2;  // Each module = 2x2 pixels
  const int offsetX = (128 - qrcode.size * scale) / 2;  // Centering
  const int offsetY = (64 - qrcode.size * scale) / 2;

  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        u8g2.drawBox(offsetX + x * scale, offsetY + y * scale, scale, scale);
      }
    }
  }

  u8g2.sendBuffer();
}

void loop() {
  // Do nothing
}
