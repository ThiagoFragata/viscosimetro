#include <Arduino.h>

#define minValue1 130
#define minValue2 876 
#define minValue3 1015

unsigned long startTime = 0;
unsigned long capturedTime = 0;

bool running = false;
bool calibrating = false;

int pinoReceptor1 = A0;
int pinoReceptor2 = A1;
int pinoReceptor3 = A2;

int pinoEletroIma = 13;
int pinoBuzzer = 7;


void setup() {
  pinMode(pinoReceptor1, INPUT);
  pinMode(pinoReceptor2, INPUT);
  pinMode(pinoReceptor3, INPUT);

  pinMode(pinoEletroIma, OUTPUT);
  pinMode(pinoEletroIma, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);

  digitalWrite(pinoEletroIma, HIGH);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    int receptor1 = analogRead(pinoReceptor1);
    int receptor2 = analogRead(pinoReceptor2);
    int receptor3 = analogRead(pinoReceptor3);

    if (command == 's') {
      digitalWrite(pinoEletroIma, LOW);
      startTime = millis();
      running = true;
    } else if (command == 'r') {
      capturedTime = millis();
      startTime = 0;
      running = false;
      calibrating = false;
      digitalWrite(pinoEletroIma, HIGH);
    } else if (command == 'c') {
      calibrating = true;
    }
  }

  if (calibrating) {
    int receptor1 = analogRead(pinoReceptor1);
    int receptor2 = analogRead(pinoReceptor2);
    int receptor3 = analogRead(pinoReceptor3);

    Serial.println(receptor1);
    Serial.println(receptor2);
    Serial.println(receptor3);
    Serial.println("**********");

    delay(500);
  }

  if (running) {
    int receptor1 = analogRead(pinoReceptor1);
    int receptor2 = analogRead(pinoReceptor2);
    int receptor3 = analogRead(pinoReceptor3);


    if (receptor1 <= (minValue1 - 2) || receptor2 <= (minValue2 - 2) || receptor3 <= (minValue3 - 2)) {
      capturedTime = millis();
      digitalWrite(pinoBuzzer, HIGH);
      delay(100);
      digitalWrite(pinoBuzzer, LOW);
    }
  }

  if (capturedTime > 0) {
    unsigned long capturedElapsed = capturedTime - startTime;
    unsigned long capturedMinutes = (capturedElapsed / 60000) % 60;
    unsigned long capturedSeconds = (capturedElapsed / 1000) % 60;
    unsigned long capturedMilliseconds = capturedElapsed % 1000;

    Serial.print("Tempo capturado: ");
    Serial.print(capturedMinutes);
    Serial.print(":");
    Serial.print(capturedSeconds);
    Serial.print(".");
    Serial.println(capturedMilliseconds);

    capturedTime = 0;  // Zera o tempo capturado
  }
}
