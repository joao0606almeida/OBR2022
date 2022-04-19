/*
Este e o arquivo principal. Seu nome de difere da convencao de "main.x" devido a restircoes do arduino IDE.
Este codigo deve ser usado com um Arduino ATMEGA 2560. Ele provavelmente nao funcionara em outros.
Nenhuma garantia sobre o funcionamente deste codigo sera oferecida, mesmo em placa suportadas pelo mesmo.
*/
#include "Libraries/Ultrasom/Ultrasom.hpp"

//definir portas de sensores/pontes com nomes para conveniencia
#define infra0 A15
#define infra1 A14
#define ponteH1 A0
#define ponteH2 A1
//definir variaveis globais de calibracao
int infraWhiteValue;
//TODO: int infraBlackValue;

/*
Funcao responsavel por calibrar sensores
*/
void calibrar(){
  delay(1000);
  int infraWhiteValue[2];
  infraWhiteValue[0] = analogRead(infra0);
  infraWhiteValue[1] = analogRead(infra1);
}

/*
Setup inicial, definir inputs, inicial calibramento, etc
*/
void setup() {
  //Definir pinos de seonsores como input
  pinMode(infra0, INPUT);
  pinMode(infra1, INPUT);
  //definir pinos de ponteH como output
  pinMode(ponteH1, OUTPUT);
  pinMode(ponteH2, OUTPUT);
  //calibrar sensores
  calibrar();
}


void loop() {
  
}
