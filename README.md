# Sistema de Controle de Estacionamento com Arduino

Sistema embarcado para gerenciar um estacionamento universitário com 20 vagas, desenvolvido para a disciplina de Sistemas Embarcados. O projeto possui duas versões, cada uma com um tipo diferente de display.

---

## 1. Versão com Display LCD (`estacionamento_lcd.ino`)

A cancela é controlada manualmente: um botão abre, outro fecha. O LCD exibe o status atual e o Serial Monitor registra cada movimentação.

O sistema inicia com a cancela fechada (LED vermelho aceso). Ao pressionar o botão de entrada, a cancela abre e o LED verde é aceso, isso só acontece se ainda houver vagas. Quando o veículo já passou, o botão de saída é pressionado, o que fecha a cancela e o LED vermelho volta a estar aceso. Se o estacionamento estiver lotado, o LED vermelho pisca três vezes e a cancela permanece fechada.

### Componentes

| Componente | Pino |
|---|---|
| Botão de entrada | 2 |
| Botão de saída | 4 |
| LED Verde | 7 |
| LED Vermelho | 8 |
| Servo Motor (cancela) | 9 |
| LCD (RS, E, D4–D7) | 13, 12, 11, 10, 6, 5 |

> Além disso: 1x potenciômetro para o contraste do LCD, 2x resistores 220 Ω para os LEDs.

### Simulação

- [Tinkercad — Versão LCD](https://www.tinkercad.com/things/bxbln3NHE4A-sistema-de-controle-de-estacionamento-lcd-?sharecode=JE2NZ-yYD0uaDjFMk3yzNADwzjPYZMcXKfjCliAB1YM)

![Esquema do Circuito - Versão LCD](<imagens/Sistema de Controle de Estacionamento - LCD .png>)

---

## 2. Versão com Display de 7 Segmentos (`estacionamento_7seg.ino`)

Nessa versão a cancela opera de forma automática: ela abre ao pressionar o botão e fecha após 3 segundos, somando ao número de carros no estacionamento, já o segundo botão funciona como uma sáida do estacionamento, então a cancela abre, e o número de vagas é diminuido antes que seja fechada novamente. O display mostra quantas vagas estão livres e é atualizado a cada interação com os botões.

O display utilizado é o módulo **Adafruit 4-Digit 7-Segment** com comunicação **I²C** (endereço `0x70`). A biblioteca `Adafruit_LEDBackpack` cuida de toda a comunicação — basta passar o número para `display.print()` e chamar `display.writeDisplay()` para atualizar o que aparece na tela.

O botão de entrada ocupa uma vaga e abre a cancela; o botão de saída libera uma vaga e também abre a cancela para o veículo sair. Quando lotado, o botão de entrada é ignorado e o LED vermelho pisca três vezes.

### Componentes

| Componente | Pino |
|---|---|
| Botão de entrada | 2 |
| Botão de saída | 4 |
| LED Verde | 7 |
| LED Vermelho | 8 |
| Servo Motor (cancela) | 9 |
| Display I²C (SDA/SCL) | A4 / A5 |

> Além disso: 2x resistores 220 Ω para os LEDs.

### Simulação

- [Tinkercad — Versão 7 Segmentos](https://www.tinkercad.com/things/d7oOhoP8BFs-sistema-de-controle-de-estacionamento-tela-de-7-segmentos-?sharecode=_1YMt9BAXqA3X_FSxMk1w2unYoon7Y6uk_H0TESiCq0)

![Esquema do Circuito - Versão 7 Segmentos](<imagens/Sistema de Controle de Estacionamento - tela de 7 segmentos .png>)

---

## Como rodar

1. Abra o arquivo `.ino` desejado na **Arduino IDE**.
2. **Versão LCD:** sem dependências extras (`LiquidCrystal` e `Servo` já vêm na IDE).
3. **Versão 7 Segmentos:** instale `Adafruit LED Backpack` e `Adafruit GFX` pelo gerenciador de bibliotecas.
4. Monte o circuito conforme o esquema e faça o upload para a placa.
5. Abra o **Serial Monitor** em **9600 baud** para ver os logs.
