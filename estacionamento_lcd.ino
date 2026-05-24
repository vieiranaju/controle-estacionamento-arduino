#include <LiquidCrystal.h>
#include <Servo.h>

#define TOTAL_VAGAS 20

#define PINO_BOTAO_ENTRADA  2   // Botao abrir
#define PINO_BOTAO_SAIDA    4   // Botao fechar
#define PINO_LED_VERDE      7   // Led verde
#define PINO_LED_VERMELHO   8   // Led vermelho
#define PINO_SERVO          9   // Servo motor

//RS=13, E=12, D4=11, D5=10, D6=6, D7=5
LiquidCrystal lcd(13, 12, 11, 10, 6, 5);

Servo catraca;

int vagasOcupadas = 0;
bool cancelaAberta = false; 

bool estadoAnteriorEntrada = HIGH;
bool estadoAnteriorSaida = HIGH;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  catraca.attach(PINO_SERVO);

  pinMode(PINO_BOTAO_ENTRADA, INPUT_PULLUP);
  pinMode(PINO_BOTAO_SAIDA, INPUT_PULLUP);
  
  pinMode(PINO_LED_VERDE, OUTPUT);
  pinMode(PINO_LED_VERMELHO, OUTPUT);

  fecharCancela();

  Serial.println("Sistema iniciado - Capacidade: 20 vagas - Vagas disponiveis: 20");
  
  atualizarLCD("Sistema iniciado", "Vagas livres: 20");

  delay(200); 
  estadoAnteriorEntrada = digitalRead(PINO_BOTAO_ENTRADA);
  estadoAnteriorSaida = digitalRead(PINO_BOTAO_SAIDA);
}

void loop() {
  // Estado atual dos botoes
  bool estadoAtualEntrada = digitalRead(PINO_BOTAO_ENTRADA);
  bool estadoAtualSaida = digitalRead(PINO_BOTAO_SAIDA);

  // Lógica do botao de entrada
  if (estadoAtualEntrada == LOW && estadoAnteriorEntrada == HIGH) {
    if (cancelaAberta == false) { 
      
      if (vagasOcupadas < TOTAL_VAGAS) {
        vagasOcupadas++;
        abrirCancela();
        
        int vagasDisponiveis = TOTAL_VAGAS - vagasOcupadas;
        
        Serial.print("Entrada registrada. Vagas ocupadas: ");
        Serial.print(vagasOcupadas);
        Serial.print(" - Vagas disponiveis: ");
        Serial.println(vagasDisponiveis);
        
        String textoVagas = "Vagas livres: " + String(vagasDisponiveis);
        atualizarLCD("Entrada liberada", textoVagas);
        
      } else {
        Serial.println("Estacionamento lotado - entrada bloqueada. Vagas: 0/20");
        atualizarLCD("Sistema lotado!", "Vagas: 0/20");
        
        piscarLedVermelho();
        atualizarLCD("Aguarde...", "Vagas: 0/20");
      }
    }
    delay(50); 
  }

  // Lógica do botao de saida 
  if (estadoAtualSaida == LOW && estadoAnteriorSaida == HIGH) {
    if (cancelaAberta == true) { 
      fecharCancela();
      
      int vagasDisponiveis = TOTAL_VAGAS - vagasOcupadas;
      
      Serial.println("Cancela fechada");
      
      String textoVagas = "Vagas livres: " + String(vagasDisponiveis);
      atualizarLCD("Cancela fechada", textoVagas);
    }
    delay(50); 
  }

  // Atualiza os estados anteriores para a proxima leitura
  estadoAnteriorEntrada = estadoAtualEntrada;
  estadoAnteriorSaida = estadoAtualSaida;
}


void abrirCancela() {
  cancelaAberta = true;
  digitalWrite(PINO_LED_VERDE, HIGH);
  digitalWrite(PINO_LED_VERMELHO, LOW);
  catraca.write(90); 
}

void fecharCancela() {
  cancelaAberta = false;
  digitalWrite(PINO_LED_VERDE, LOW);
  digitalWrite(PINO_LED_VERMELHO, HIGH);
  catraca.write(0);  
}

void piscarLedVermelho() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(PINO_LED_VERMELHO, LOW);
    delay(150);
    digitalWrite(PINO_LED_VERMELHO, HIGH);
    delay(150);
  }
}

void atualizarLCD(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
}