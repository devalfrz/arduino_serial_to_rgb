/*
 *
 *  Reads 3 bytes (RGB) from the serial input
 *  and displays them on 3 analog outputs.
 *  PIN09 - RED
 *  PIN10 - GREEN
 *  PIN11 - BLUE
 *  PIN06 - NeoPixel Strip
 *  
 *  SERIAL_BAUD: 115200
 *
 *  Alfredo Rius
 *  alfredo.rius@gmail.com
 *
 *  Change log
 *  v1.1 - 2018-12-14
 *    Added NeoPixels
 *  
 *  v1.0 - 2018-10-13:
 *    Production
 *  
*/ 

#define STRIP_LENGTH 300

#include <Adafruit_NeoPixel.h>

#define R_LED 9
#define G_LED 10
#define B_LED 11
#define NEO 6

uint8_t data[10];
uint8_t incomingByte = 0;
uint8_t i=0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LENGTH, NEO, NEO_GRB + NEO_KHZ800);

// Set color
void colorFill(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void setup() {
  Serial.begin(115200); 
  pinMode(R_LED,OUTPUT);
  pinMode(G_LED,OUTPUT);
  pinMode(B_LED,OUTPUT);
  strip.begin();
  strip.show();
}

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte != 10){
      if(i<3){
        Serial.print(incomingByte, DEC);
        data[i] = incomingByte;
        i++;
         if(i<3) Serial.print(",");
      }
    }else{
      Serial.println("");
      i=0;
      analogWrite(B_LED,data[0]);
      analogWrite(G_LED,data[1]);
      analogWrite(R_LED,data[2]);
      colorFill(strip.Color(data[0],data[1],data[2]));
    }
  }
}
