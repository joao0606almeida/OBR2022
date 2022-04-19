/*
Biblioteca feita para o sensor ultrassonico HS04. nehuma garantia de funcionamento com outros sensores.
Nehuma garantia mesmo no sensor HS04, embora teoricamente deva funcionar.
*/
#ifndef Ultrasom
#define Ultrasom
#include <Arduino.h>

class Sensor{
private:
  byte EchoPin = 0;
  byte TriggerPin = 0;
    public:
        Sensor(byte Trigger, byte Echo){
            EchoPin = Echo;
            TriggerPin = Trigger;
            pinMode(Trigger, OUTPUT);
            pinMode(EchoPin, INPUT);
        }
        float MedirDistancia(byte Echo, byte Trigger){
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
        float MedirDistancia(){
            return MedirDistancia(EchoPin, TriggerPin);
        }
};

#endif
