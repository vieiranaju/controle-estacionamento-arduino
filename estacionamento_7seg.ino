#include <Wire.h>
#include <Servo.h>
#include <Adafruit_LEDBackpack.h>

#define TOTAL_VAGAS 20

#define PINO_BOTAO_ENTRADA  2   // Botao de entrada
#define PINO_BOTAO_SAIDA    4   // Botao de saida
#define PINO_LED_VERDE      7   // Led verde
#define PINO_LED_VERMELHO   8   // Led vermelho
#define PINO_SERVO          9   // Servo motor

Adafruit_7segment display = Adafruit_7segment();
Servo cancela;

int vagasOcupadas = 0;

bool estadoAnteriorEntrada = HIGH;
bool estadoAnteriorSaida = HIGH;

void setup() {
  Serial.begin(9600);
  
  pinMode(PINO_BOTAO_ENTRADA, INPUT_PULLUP);
  pinMode(PINO_BOTAO_SAIDA, INPUT_PULLUP);
  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_LED_VERMELHO, OUTPUT);

  cancela.attach(PINO_SERVO);
  cancela.write(0); 

  delay(1000); 

  display.begin(0x70);
  atualizarDisplay();
  
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, HIGH);
  
  estadoAnteriorEntrada = digitalRead(PINO_BOTAO_ENTRADA);
  estadoAnteriorSaida   = digitalRead(PINO_BOTAO_SAIDA);

  Serial.println("Estacionamento iniciado - Capacidade: 20 vagas");
}

void loop() {
  // Estado atual dos botoes
  bool estadoAtualEntrada = digitalRead(PINO_BOTAO_ENTRADA);
  bool estadoAtualSaida   = digitalRead(PINO_BOTAO_SAIDA);

  // Entrada
  if (estadoAtualEntrada == LOW && estadoAnteriorEntrada == HIGH) {
    delay(50); 
    
    if (digitalRead(PINO_BOTAO_ENTRADA) == LOW) {
      if (vagasOcupadas < TOTAL_VAGAS) {
        vagasOcupadas++;
        atualizarDisplay();
        
        Serial.print("Entrada registrada. Ocupadas: ");
        Serial.print(vagasOcupadas);
        Serial.print(" - Livres: ");
        Serial.println(TOTAL_VAGAS - vagasOcupadas);
        
        abrirCancela();
      } else {
        Serial.println("Estacionamento lotado. Entrada bloqueada.");
        piscarVermelhoLotado();
      }
    }
  }

  // Saida
  if (estadoAtualSaida == LOW && estadoAnteriorSaida == HIGH) {
    delay(50); 
    
    if (digitalRead(PINO_BOTAO_SAIDA) == LOW) {
      if (vagasOcupadas > 0) {
        vagasOcupadas--;
        atualizarDisplay();
        
        Serial.print("Saida registrada. Ocupadas: ");
        Serial.print(vagasOcupadas);
        Serial.print(" - Livres: ");
        Serial.println(TOTAL_VAGAS - vagasOcupadas);
        
        abrirCancela();
      } else {
        Serial.println("Estacionamento ja vazio.");
      }
    }
  }

  estadoAnteriorEntrada = estadoAtualEntrada;
  estadoAnteriorSaida   = estadoAtualSaida;
}

void abrirCancela() {
  digitalWrite(PINO_LED_VERMELHO, LOW);
  digitalWrite(PINO_LED_VERDE, HIGH);
  
  cancela.write(90); 
  delay(3000); 
  
  cancela.write(0);  
  delay(1000); 
  
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, HIGH);
}

void piscarVermelhoLotado() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(PINO_LED_VERMELHO, LOW); 
    delay(200);
    digitalWrite(PINO_LED_VERMELHO, HIGH); 
    delay(200);
  }
}

void atualizarDisplay() {
  display.print(TOTAL_VAGAS - vagasOcupadas, DEC);
  display.writeDisplay();
}