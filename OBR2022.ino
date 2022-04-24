/*
Este e o arquivo principal. Seu nome de difere da convencao de "main.x" devido a restircoes do arduino IDE.
Este codigo deve ser usado com um Arduino ATMEGA 2560. Ele provavelmente nao funcionara em outros.
Adiocionalmente, como definido nos seus respectivos arquivos, a bibliotecas Ultrasom.hpp e PonteH.hpp sao, 
respectivamente, feitas para sesnores HC-SR04, ponteH L298N. A biblioteca Infrared.hpp deve funcionar com qualquer sensor, 
DESDE que seu input seja por um UNICO pino analogico.  Provavelmenta nao funcionarao com outros(as).
Nenhuma garantia sobre o funcionamente deste codigo sera oferecida, mesmo em placa suportadas pelo mesmo.
*/
#include "Libraries/Ultrasom/Ultrasom.hpp"
#include "Libraries/PonteH/PonteH.hpp"
#include "Libraries/Infrared/Infrared.hpp"

//definir portas de sensores/pontes com nomes para conveniencia
#define infra0 A15
#define infra1 A14
#define ponteI1 31
#define ponteI2 33
#define ponteI3 35
#define ponteI4 37
#define ponteENA 2
#define ponteENB 3

//initializar varaveis globais
volatile float fowardDistance;
volatile long fowardTime = micros();
volatile bool fowardCall;
//initializar partes do robo
Ponteh *ponte = new Ponteh(ponteI1, ponteI2, ponteI3, ponteI4, ponteENA, ponteENB);
InfraredSensor *inf0 = new InfraredSensor(infra0);
InfraredSensor *inf1 = new InfraredSensor(infra1);
UltrassonicSensor *foward = new UltrassonicSensor(1,2);


void fowardIsr(){
  long currentTime = micros();
  long duracao = currentTime - fowardTime;
  fowardDistance = ((float)duracao/2) / 29.1;
  fowardCall = true;
}

/*
Setup inicial, calibracao de sensores
TODO: Calibracao multi-etapa para verde
*/
void setup() {
  //setar velocidade
  ponte->setSpeed(80);
  //esperar os sensores ligarem
  delay(1000);
  //calibrar sensores
  inf0->calibrateWhite();
  inf1->calibrateWhite();
  attachInterrupt(digitalPinToInterrupt(foward->getEcho()), fowardIsr, RISING);
  foward->trigger();
  fowardTime = millis();
}

void interruptsCheck(){
  if(fowardCall){
    fowardCall = false;
    foward->trigger();
  }
}

void loop() {
  interruptsCheck();
  //TODO:Logica para os verdes
  if(inf0->read()==Color::WHITE&&inf1->read()==Color::WHITE){
      //tudo branco, frente
      ponte->foward();
  }else if(inf0->read()==Color::WHITE&&inf1->read()==Color::BLACK){
      //direita preto, direita
      ponte->right();
  }else if(inf0->read()==Color::BLACK&&inf1->read()==Color::WHITE){
      //esquerda preto, esquerda
      ponte->left();
  }else{
      //Dois pretos, frente
      ponte->foward();
      delay(1000);
  }
}
