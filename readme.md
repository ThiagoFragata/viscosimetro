# Projeto Arduino: Viscosímetro

Este projeto utiliza um Arduino para capturar o tempo de reação com base em leituras de três sensores. O sistema ativa um eletroímã e um buzzer para indicar eventos específicos. Este README fornecerá instruções detalhadas sobre como configurar e calibrar os sensores, além de listar as dependências necessárias.

## Materiais Necessários

- 1x Arduino (UNO, Mega, etc.)
- 3x Sensores analógicos (conectados aos pinos A0, A1, A2)
- 1x Eletroímã (conectado ao pino 13)
- 1x Buzzer (conectado ao pino 7)
- Jumpers e protoboard
- Fonte de alimentação (se necessário)

## Conexões

1. **Sensores**:
   - Sensor 1: Sinal ao pino A0
   - Sensor 2: Sinal ao pino A1
   - Sensor 3: Sinal ao pino A2

2. **Eletroímã**:
   - Pino de controle: pino 13 (conectado ao terminal positivo do eletroímã)
   - Terminal negativo do eletroímã: GND

3. **Buzzer**:
   - Pino de controle: pino 7
   - Outro terminal do buzzer: GND

## Código

O código Arduino está disponível no arquivo `viscosimetro.ino`. Faça o upload deste código para o seu Arduino usando a IDE Arduino.

```cpp
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
```

## Comandos

Você pode enviar comandos para o Arduino via Serial Monitor para controlar o comportamento do sistema:

- s: Inicia a captura de tempo e desativa o eletroímã.
- r: Reseta o tempo capturado e reativa o eletroímã.
- c: Entra no modo de calibração dos sensores.

## Calibração dos Sensores

- Conecte seu Arduino ao computador e abra o Serial Monitor na IDE Arduino.
- Envie o comando c para entrar no modo de calibração.
- Observe os valores dos sensores no Serial Monitor e anote os valores mínimos que você deseja usar.
- Atualize as definições minValue1, minValue2, e minValue3 no código com os valores anotados.
- Refaça o upload do código atualizado para o Arduino.

## Dependências

Este projeto não possui dependências externas além da IDE Arduino.


## Autor

Desenvolvido por Thiago Fragata.

- [GitHub](https://github.com/ThiagoFragata)
- [LinkedIn](https://www.linkedin.com/in/thiagohenriquefragata)

Sinta-se à vontade para entrar em contato e contribuir para o projeto!

# Licença

Este projeto é de código aberto e pode ser usado livremente para fins educacionais e pessoais.