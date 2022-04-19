/*
Bibioteca feita para ponteH L298N. Nao a nenhuma garantia de funcionamento para outras pontes.
Nenhuma garantia de funcionamento, embora teoricamente deva funcionar, mesmo na ponte L298N.
*/
#ifndef PonteH
#define PonteH
#include <Arduino.h>

class Ponteh{
private:
  byte I1 = 0;
  byte I2 = 0;
  byte I3 = 0;
  byte I4 = 0;
  byte ENA = 0;
  byte ENB = 0;
    public:
        Ponteh(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6){
            I1 = pin1;
            I2 = pin2;
            I3 = pin3;
            I4 = pin4;
            ENA = pin5;
            ENB = pin6;
            pinMode(I1, OUTPUT);
            pinMode(I2, OUTPUT);
            pinMode(I3, OUTPUT);
            pinMode(I4, OUTPUT);
            pinMode(ENA, OUTPUT);
            pinMode(ENB, OUTPUT);
        }
        void setSpeed(int speed){
          analogWrite(ENA, speed);
          analogWrite(ENB, speed);
        }
        void setSpeedRightSide(int speed){
          analogWrite(ENB, speed);
        }
        void setSpeedLeftSide(int speed){
          analogWrite(ENA, speed);
        }
        void foward(){
          digitalWrite(I1, HIGH);
          digitalWrite(I2, LOW);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, LOW);
        }
        void left(){
          digitalWrite(I1, HIGH);
          digitalWrite(I2, LOW);
          digitalWrite(I3, LOW);
          digitalWrite(I4, HIGH);
        }
        void right(){
          digitalWrite(I1, LOW);
          digitalWrite(I2, HIGH);
          digitalWrite(I3, HIGH);
          digitalWrite(I4, LOW);
        }
};

#endif
