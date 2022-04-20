/*
Este e o arquivo principal. Seu nome de difere da convencao de "main.x" devido a restircoes do arduino IDE.
Este codigo deve ser usado com um Arduino ATMEGA 2560. Ele provavelmente nao funcionara em outros.
Adiocionalmente, como definido nos seus respectivos arquivos, a bibliotecas Ultrasom.hpp e PonteH.hpp sao, 
respectivamente, feitas para sesnores HC-SR04 e ponteH L298N. Provavelmenta nao funcionarao com outras.
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

//initializar partes do robo
Ponteh *ponte = new Ponteh(ponteI1, ponteI2, ponteI3, ponteI4, ponteENA, ponteENB);
InfraredSensor *inf0 = new InfraredSensor(infra0);
InfraredSensor *inf1 = new InfraredSensor(infra1);

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
}

void loop() {
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
