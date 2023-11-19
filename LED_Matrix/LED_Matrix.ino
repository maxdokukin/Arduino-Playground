#include "Adafruit_NeoPixel.h"
#include "FastLED.h"


#define LED_PIN 4
#define LED_NUM 64
#define MAX_BRIGHTNESS 255

Adafruit_NeoPixel squareMatrix(LED_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel circleMatrix(61, 3, NEO_GRB + NEO_KHZ800);

#include "Potentiometer.h"

Potentiometer *pot0, *pot1;

void setup() {

  // Serial.begin(115200);
  // delay(4000);

  squareMatrix.begin();
  squareMatrix.setBrightness(255);  //getMemBright());
  squareMatrix.clear();
  squareMatrix.show();
  
  circleMatrix.begin();
  circleMatrix.setBrightness(255);  //getMemBright());
  circleMatrix.clear();
  circleMatrix.show();
}

//uint16_t hue = 0;

void loop() {

  // pot0->update();
  // pot1->update();

  perlin(27000, 40000, 30, 200);

  squareMatrix.show();

  // Serial.print(analogRead(A0));
  // Serial.print(",");
  // Serial.print(pot0->getValue());
  // Serial.print(",");
  // Serial.print(analogRead(A1));
  // Serial.print(",");
  // Serial.println(pot1->getValue());

//   int value1, value2;
//   value1 = random(1000,6000);
//   Serial.print(value1);
//   Serial.print(",");
//   value2 = random(0,3000);
//   Serial.println(value2);
//   delay(100);
}


uint16_t perlinCounter = 0;


void perlin(unsigned int hueStart, unsigned int hueGap, byte fireStep, byte minSat) {

  for (int i = 0; i < LED_NUM; i++)
    squareMatrix.setPixelColor(i, getFireColor(hueStart, hueGap, minSat, (inoise8(i * fireStep, perlinCounter))));

  perlinCounter += 3;
}


long getFireColor(unsigned int hueStart, unsigned int hueGap, byte minSat, int val) {


  return squareMatrix.ColorHSV(
    ((long)hueStart + (long)map(val, 0, 255, 0, hueGap)) % 65535,  //H
    constrain(map(val, 0, 255, minSat, 255), 0, 255),              //S
    constrain(map(val, 0, 255, 10, MAX_BRIGHTNESS), 0, 255)        //V
  );
}