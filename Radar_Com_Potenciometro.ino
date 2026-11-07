#include <Servo.h>

#define POT A0
#define SERVO 11
#define TRIG 9
#define ECHO 10
#define LED 3

Servo servo;

int valorPot = 0;
int angulo = 0;
int brilho = 0;
// float limiteDistancia = 15.0;

float medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracao = pulseIn(ECHO, HIGH, 10000);

  if (duracao == 0) {
    return -1;
  }

  return duracao * 0.0343 / 2;
}

void lerDistancia(int angulo) {
  float distancia = medirDistancia();
  distancia = constrain(distancia, 0, 100);

  brilho = map(distancia, 100, 0, 0, 255);

  if (distancia < 0) {
    Serial.println("Sem retorno");
  }

  // DETECCAO DE OBSTACULOS
  if (distancia > 0) {
    analogWrite(LED, brilho);

    Serial.print("\nAlvo detectado em: ");
    Serial.print(angulo);
    Serial.print("° e ");
    Serial.print(distancia);
    Serial.println("cm\n");
  } 
  else {
    analogWrite(LED, 0);
    brilho = 0;

    Serial.println("\nNenhum alvo detectado");
  }
}

void girarServo(int angulo){
  servo.write(angulo);
  delay(15);
}

void setup() {
  Serial.begin(9600);

  servo.attach(SERVO);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);

  Serial.println("\nTerminal do potenciometro\n");
}

void loop() {
  valorPot = analogRead(POT);

  angulo = map(valorPot, 0, 1023, 0, 170);
  
  girarServo(angulo);
  lerDistancia(angulo);
}
