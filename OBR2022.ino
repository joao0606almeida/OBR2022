/*
Este e o arquivo principal. Seu nome de difere da convencao de "main.x" devido a restircoes do arduino IDE.
Este codigo deve ser usado com um Arduino ATMEGA 2560. Ele provavelmente nao funcionara em outros.
Nenhuma garantia sobre o funcionamente deste codigo sera oferecida, mesmo em placa suportadas pelo mesmo.
*/
#include "Libraries/Ultrasom/Ultrasom.hpp"

//definir portas de sensores/pontes com nomes para conveniencia
#define infra0 A15
#define infra1 A14
#define ponteI1 31
#define ponteI2 33
#define ponteI3 35
#define ponteI4 37
#define ponteENA 2
#define ponteENB 3
//definir variaveis globais de calibracao
int infraWhiteValue[2];
//TODO: int infraBlackValue;

/*
Funcao responsavel por calibrar sensores
*/
void calibrar(){
  delay(1000);
  //multiplicamos por mil para diminuir as diferencas da imprecisao de sensores
  infraWhiteValue[0] = analogRead(infra0)*1000;
  infraWhiteValue[1] = analogRead(infra1)*1000;
}

/*
Setup inicial, definir inputs, inicial calibramento, etc
*/
void setup() {
  //Definir pinos de seonsores como input
  pinMode(infra0, INPUT);
  pinMode(infra1, INPUT);
  //definir pinos de ponteH como output
  pinMode(ponteI1, OUTPUT);
  pinMode(ponteI2, OUTPUT);
  pinMode(ponteI3, OUTPUT);
  pinMode(ponteI4, OUTPUT);
  digitalWrite(ponteI1, LOW);
  digitalWrite(ponteI2, LOW);
  digitalWrite(ponteI3, LOW);
  digitalWrite(ponteI4, LOW);
  //calibrar sensores
  calibrar();
}

/*
Funcao de conveniciencia, checka se e branco ou nao
*/
bool ehBranco(int sensorInput, int index){
  if(sensorInput*1000>=infraWhiteValue[index]){
    return true;
  }else{
    return false;
  }
}

void loop() {
  analogWrite(ponteENA, 80);
  analogWrite(ponteENB, 80);
  if(ehBranco(analogRead(infra0),0)&&ehBranco(analogRead(infra1),1)){
      //tudo branco, frente
      digitalWrite(ponteI1, HIGH);
      digitalWrite(ponteI2, LOW);
      digitalWrite(ponteI3, HIGH);
      digitalWrite(ponteI4, LOW);
  }else if(ehBranco(analogRead(infra0),0)){
      //direita preto, direita
      digitalWrite(ponteI1, LOW);
      digitalWrite(ponteI2, HIGH);
      digitalWrite(ponteI3, HIGH);
      digitalWrite(ponteI4, LOW);
  }else if(ehBranco(analogRead(infra1),1)){
      //esquerda preto, esquerda
      digitalWrite(ponteI1, HIGH);
      digitalWrite(ponteI2, LOW);
      digitalWrite(ponteI3, LOW);
      digitalWrite(ponteI4, HIGH);
  }else{
      //TODO: AJEITAR ISSO, NAO FUNCIONA
      digitalWrite(ponteI1, HIGH);
      digitalWrite(ponteI2, LOW);
      digitalWrite(ponteI3, HIGH);
      digitalWrite(ponteI4, LOW);
      delay(1000);
  }
}
