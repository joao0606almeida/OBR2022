#ifndef Infrared
#define Infrared
#include <Arduino.h>
/*
Biblioteca para facilitar o uso de sensores infravermelhos.
Deeve funcionar com qualquer um, desde que seu input seja um UNICO pino analogico
*/
struct Color{
  typedef enum {WHITE, GREEN, BLACK} COLOR;
};

class InfraredSensor{
  private:
    byte inputPin;
    int ambientWhite;
    int ambientGreen;
  public:
    InfraredSensor(byte input){
      inputPin = input;
      pinMode(input, INPUT);
    }
    void calibrateWhite(){
      ambientWhite = analogRead(inputPin)*2048;
    }
    void calibrateGreen(){
      ambientGreen = analogRead(inputPin)*2048;
    }
    Color::COLOR read(){
      Color::COLOR trueRead;
      Color::COLOR read;
      Color::COLOR read1;
      Color::COLOR read2;

      int rawRead = analogRead(inputPin)*2048;
      delayMicroseconds(100);
      int rawRead1 = analogRead(inputPin)*2048;
      delayMicroseconds(100);
      int rawRead2 = analogRead(inputPin)*2048;

      if(rawRead>=ambientWhite){
        read = Color::WHITE;
      }else if(rawRead>=ambientGreen){
        read = Color::GREEN;
      }else{
        read = Color::BLACK;
      }

      if(rawRead1>=ambientWhite){
        read1 = Color::WHITE;
      }else if(rawRead1>=ambientGreen){
        read1 = Color::GREEN;
      }else{
        read1 = Color::BLACK;
      }

      if(rawRead2>=ambientWhite){
        read2 = Color::WHITE;
      }else if(rawRead2>=ambientGreen){
        read2 = Color::GREEN;
      }else{
        read2 = Color::BLACK;
      }

      if(read==read1||read==read2){
          return read;
      }else if(read1==read2){
          return read1;
      }else{
        return read2;
      }


    }
};

#endif
