#include <Ultrasonic.h>

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

bool inicioConcluido = false;

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

  pinMode(ledverde, OUTPUT); 
  pinMode(ledVermelho, OUTPUT); 

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  Serial.begin(9600);
}

void AndarFrente(){
    //para frente
    analogWrite (pwmA, 100);
    analogWrite (pwmB, 100);
}

void PararMotor(){
  digitalWrite(pwmA, LOW);
  digitalWrite(pwmB, LOW);
}

void ViraMotorBEsquerda(){
      //esquerda
    digitalWrite(pwmA, LOW);
    analogWrite (pwmB, 100);
}

void ViraMotorADireita(){
      //direita
    analogWrite (pwmA, 100);
    digitalWrite(pwmB, LOW);
}

int SensorSonic(){

  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);  

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2; // em cm
  return distance;
}

void AcenderLedVermelha(){
  digitalWrite(ledVermelho, LOW);
}

void DesligarLedVermelha(){
  digitalWrite(ledVermelho, HIGH);
}

void AcenderLedVerde(){
  digitalWrite(ledverde, HIGH);
}

void SensorLuz(){

  leituraC = digitalRead(sensor_centro); //preto é 1, branco é 0
  leituraD = digitalRead(sensor_direita); //preto é 1, branco é 0
  leituraE = digitalRead(sensor_esquerda); //preto é 1, branco é 0
}

void loop() {
  
 
 if (!inicioConcluido) { 
    DesligarLedVermelha();
    delay(5000);// 5000 milissegundos = 5 segundos
    inicioConcluido = true;
  }
    SensorSonic();
    Serial.println(distance);
    SensorLuz();
    DesligarLedVermelha();
    AcenderLedVerde();
    if (distance <= 5) {
      AcenderLedVermelha();
      PararMotor();
    }else{
      //Seguir linha 
    SensorLuz();
    if(leituraC == 0){
      AndarFrente();
    }
    if(leituraD == 0){
      ViraMotorADireita();
    }
    if(leituraE == 0){
      ViraMotorBEsquerda();
    }
  }

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





