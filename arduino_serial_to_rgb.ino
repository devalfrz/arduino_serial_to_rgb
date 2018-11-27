/*
 *
 *  Reads 3 bytes (RGB) from the serial input
 *  and displays them on 3 analog outputs.
 *  PIN09 - RED
 *  PIN10 - GREEN
 *  PIN11 - BLUE
 *
 *  SERIAL_BAUD: 115200
 *
 *  Alfredo Rius
 *  alfredo.rius@gmail.com
 *
 *  Change log
 *  v1.0 - 2018-10-13:
 *    Production
 *  
*/ 


uint8_t data[3];
uint8_t incomingByte = 0;
uint8_t i=0;


void setup() {
  Serial.begin(115200); 
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
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
      analogWrite(10,data[0]);
      analogWrite(11,data[1]);
      analogWrite(9,data[2]);
    }
  }
}
