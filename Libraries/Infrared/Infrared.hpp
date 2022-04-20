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
      ambientWhite = analogRead(inputPin)*1000;
    }
    void calibrateGreen(){
      ambientGreen = analogRead(inputPin)*1000;
    }
    Color::COLOR read(){
      int read = analogRead(inputPin)*1000;
      if(read>=ambientWhite){
        return Color::WHITE;
      }if(read>=ambientGreen){
        return Color::GREEN;
      }else{
        return Color::BLACK;
      }
    }

};

#endif
