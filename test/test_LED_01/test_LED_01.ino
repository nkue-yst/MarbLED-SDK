#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

constexpr int WIDTH  = 8;
constexpr int HEIGHT = 8;

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  Serial.begin(115200);

  matrix.begin(0x70);
  matrix.setRotation(3);

  for (int y = 1; y <= HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      matrix.clear();
      matrix.drawPixel(x, y % HEIGHT, 1);
      matrix.writeDisplay();
      delay(100);
    }
  }
  
/*
  matrix.fillCircle(4, 4, 3, 1);
  matrix.writeDisplay();
*/
}

void loop() {

}
