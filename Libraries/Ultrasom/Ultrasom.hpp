/*
Biblioteca feita para o sensor ultrassonico HC-SR04. nehuma garantia de funcionamento com outros sensores.
Nehuma garantia mesmo no sensor HC-SR04, embora teoricamente deva funcionar.
*/
#ifndef Ultrassonic
#define Ultrassonic
#include <Arduino.h>

class UltrassonicSensor{
private:
  byte EchoPin = 0;
  byte TriggerPin = 0;
  float isrRead = 0;
  bool useISR;
  long isrTimer;
    public:
        UltrassonicSensor(byte Trigger, byte Echo){
            EchoPin = Echo;
            TriggerPin = Trigger;
            pinMode(Trigger, OUTPUT);
            pinMode(EchoPin, INPUT);
            switch(EchoPin){
              case 2:
                useISR=true;
                break;
              case 3:
                useISR=true;
                break;
              case 18:
                useISR=true;
                break;
              case 19:
                useISR=true;
                break;
              case 20:
                useISR=true;
                break;
              case 21:
                useISR=true;
                break;
              default:
                useISR=false;
                break;
            }
            if(useISR){
              attachInterrupt(digitalPinToInterrupt(EchoPin), isr , RISING);
            }
        }
        UltrassonicSensor(byte Trigger, byte Echo, bool doIsr){
          EchoPin = Echo;
          TriggerPin = Trigger;
          pinMode(Trigger, OUTPUT);
          pinMode(EchoPin, INPUT);
          useISR=doIsr;
        }
        float measure(byte Echo, byte Trigger){
            long duracao, cm;
            //limpar trigger pin, evite missfires
            digitalWrite(TriggerPin, LOW);
            delayMicroseconds(5);
            //trigger
            digitalWrite(TriggerPin, HIGH);
            delayMicroseconds(10);
            digitalWrite(TriggerPin, LOW);
            //receber duracao do echo
            pinMode(EchoPin, INPUT);
            duracao = pulseIn(EchoPin, HIGH);
            //converter em cm, e retornar
            cm = (duracao/2) / 29.1;
            return cm;
        }
        float read(){
            if(useISR) return isrRead;
            return measure(EchoPin, TriggerPin);
        }
        void isr(){
          if(isrTimer!=0){
            long duracao = micros()-isrTimer;
            isrRead = (duracao/2) / 29.1;
          }
          long builtInTimer = micros();
          digitalWrite(TriggerPin, LOW);
          while(builtInTimer+5<micros()){}
          digitalWrite(TriggerPin, HIGH);
          builtInTimer = micros();
          while(builtInTimer+10<micros()){}
          digitalWrite(TriggerPin, LOW);
          isrTimer=micros();
        }
};

#endif
