/*
  L298P-Motor-Driver-Shield
  made on 09 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home
*/
#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO


int pwmA = 10;
int pwmB = 11;
int enA = 12;
int enB = 13;
int buz = 4;

int sensor_esquerda = 7;
int sensor_centro = 8;
int sensor_direita = 9;

int trigPin = 6;
int echoPin = 5;

int ledverde = 1;
int ledVermelho = 2;

Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS DO ARDUINO
int distancia; //VARIÁVEL DO TIPO INTEIRO
String result; //VARIÁVEL DO TIPO STRING


long duration;
int distance; 
int leituraE;
int leituraD;
int leituraC;

void setup() {
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(buz, OUTPUT);


  pinMode(sensor_esquerda, INPUT);
  pinMode(sensor_centro, INPUT);
  pinMode(sensor_direita, INPUT);

  
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);   

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  Serial.begin(9600);
}



void AndarFrente(){

    //para frente
    digitalWrite(pwmA, HIGH);
    digitalWrite(pwmB, HIGH);

}

void ViraMotorBEsquerda(){
      //esquerda
    digitalWrite(pwmA, LOW);
    digitalWrite(pwmB, HIGH);
}

void ViraMotorADireita(){
      //direita
    analogWrite (pwmA, 125);
    analogWrite (pwmB, 125);
}

int SensorSonic(){

  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
	delay(100);

}

void SensorLuz(){

  leituraC = digitalRead(sensor_centro); //preto é 1, branco é 0
  leituraD = digitalRead(sensor_direita); //preto é 1, branco é 0
  leituraE = digitalRead(sensor_esquerda); //preto é 1, branco é 0
  delay(250);
}




void loop() {


    SensorSonic();
    Serial.println(distance);

}



void hcsr04(){
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
    delayMicroseconds(2); //INTERVALO DE 2 MICROSSEGUNDOS
    digitalWrite(trigPin, HIGH); //SETA O PINO 6 COM PULSO ALTO "HIGH"
    delayMicroseconds(10); //INTERVALO DE 10 MICROSSEGUNDOS
    digitalWrite(trigPin, LOW); //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
    //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
    //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
    //NA VARIAVEL "distancia"
    distancia = (ultrasonic.Ranging(CM)); //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
    result = String(distancia); //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
    delay(500); //INTERVALO DE 500 MILISSEGUNDOS
 }
