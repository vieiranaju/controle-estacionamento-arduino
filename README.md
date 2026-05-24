# Sistema de Controle de Estacionamento com Arduino

Sistema embarcado desenvolvido para gerenciar um estacionamento universitário com 20 vagas. O projeto conta com duas versões complementares — uma com display LCD e outra com display de 7 segmentos —, ambas simuladas no Tinkercad e programadas em C++ para Arduino.

---

## 1. Versão com Display LCD (`estacionamento_lcd.ino`)

Nesta versão, o foco está em fornecer ao operador feedback textual completo sobre o estado do sistema. A cancela é controlada manualmente em duas etapas: o operador abre para o veículo entrar e fecha assim que o veículo passou.

### Como funciona

- **Estado inicial:** Ao ligar, a cancela começa fechada, o LED vermelho acende e o LCD exibe a mensagem de boas-vindas com o total de vagas disponíveis. O Serial Monitor também registra a inicialização.
- **Botão de entrada (pino 2):** Ao ser pressionado, o sistema verifica se ainda há vagas. Se sim, a cancela abre (servo gira para 90°), o LED verde acende no lugar do vermelho, o contador de vagas ocupadas é incrementado e o LCD é atualizado com o número de vagas restantes.
- **Botão de saída (pino 4):** Indica que o veículo já passou pela cancela. Ao ser pressionado, a cancela fecha (servo volta para 0°), o LED vermelho volta a acender e o LCD exibe a confirmação.
- **Estacionamento lotado:** Se todas as 20 vagas estiverem ocupadas, pressionar o botão de entrada não abre a cancela. O LED vermelho pisca três vezes rapidamente, o LCD exibe o aviso de lotação e o Serial Monitor registra a tentativa bloqueada.
- **Estado persistente:** O estado da cancela é mantido em memória — ela permanece aberta ou fechada até que o botão correspondente seja acionado, sem repetir ações enquanto o botão estiver pressionado.
- **Serial Monitor (9600 baud):** Cada ação gera exatamente uma mensagem de log: inicialização, entrada registrada com contagem atualizada, fechamento da cancela ou aviso de lotação.

### Componentes Utilizados

| Componente | Quantidade |
|---|---|
| Arduino Uno | 1x |
| Servo Motor (simula a cancela) | 1x |
| Display LCD 16×2 | 1x |
| Potenciômetro (contraste do LCD) | 1x |
| Pushbutton | 2x |
| LED Verde + LED Vermelho | 1x cada |
| Resistor 220 Ω | 2x |
| Protoboard e Jumpers | — |

### Link e Esquema do Circuito (LCD)

- [Acesse a simulação no Tinkercad — Versão LCD](https://www.tinkercad.com/things/bxbln3NHE4A-sistema-de-controle-de-estacionamento-lcd-?sharecode=JE2NZ-yYD0uaDjFMk3yzNADwzjPYZMcXKfjCliAB1YM)

![Esquema do Circuito - Versão LCD](<imagens/Sistema de Controle de Estacionamento - LCD .png>)

---

## 2. Versão com Display de 7 Segmentos (`estacionamento_7seg.ino`)

Nesta versão, a prioridade é mostrar o número de vagas livres de forma direta e instantânea através de um display numérico. O comportamento da cancela também é diferente: ela opera de forma automática, abrindo e fechando sozinha após um tempo fixo, sem necessidade de uma segunda ação do operador.

### Como funciona

O display de 7 segmentos utilizado é o **Adafruit 0.56" 4-Digit 7-Segment Display**, que se comunica com o Arduino pelo protocolo **I²C** (pinos SDA e SCL). A biblioteca `Adafruit_LEDBackpack` é responsável por enviar os dados ao display: basta chamar `display.print()` com o valor inteiro e depois `display.writeDisplay()` para atualizar o que aparece na tela. O endereço I²C padrão do módulo é `0x70`.

- **Botão de entrada (pino 2):** Ao ser pressionado, o sistema verifica se há vagas. Se sim, incrementa o contador de vagas ocupadas, atualiza o número no display, abre a cancela (LED verde acende, servo vai para 90°) e, após 3 segundos, fecha automaticamente (servo volta para 0°, LED vermelho volta a acender).
- **Botão de saída (pino 4):** Ao ser pressionado, o contador de vagas ocupadas é decrementado, o display é atualizado com o novo número de vagas livres e a cancela abre por 3 segundos para o veículo sair, fechando em seguida da mesma forma automática.
- **Estacionamento lotado:** Com 20 vagas ocupadas, o botão de entrada não abre a cancela. O LED vermelho pisca três vezes e o Serial Monitor registra a tentativa bloqueada.
- **Serial Monitor (9600 baud):** Registra cada movimentação com o número de vagas ocupadas e livres no momento da ação.

### Componentes Utilizados

| Componente | Quantidade |
|---|---|
| Arduino Uno | 1x |
| Servo Motor (simula a cancela) | 1x |
| Display de 7 Segmentos I²C (Adafruit LED Backpack) | 1x |
| Pushbutton | 2x |
| LED Verde + LED Vermelho | 1x cada |
| Resistor 220 Ω | 2x |
| Protoboard e Jumpers | — |

### Link e Esquema do Circuito (7 Segmentos)

- [Acesse a simulação no Tinkercad — Versão 7 Segmentos](https://www.tinkercad.com/things/d7oOhoP8BFs-sistema-de-controle-de-estacionamento-tela-de-7-segmentos-?sharecode=_1YMt9BAXqA3X_FSxMk1w2unYoon7Y6uk_H0TESiCq0)

![Esquema do Circuito - Versão 7 Segmentos](<imagens/Sistema de Controle de Estacionamento - tela de 7 segmentos .png>)

---

## Como rodar o código

1. Faça o download do arquivo `.ino` desejado.
2. Abra-o na **Arduino IDE**.
3. **Versão LCD:** nenhuma biblioteca extra é necessária — `LiquidCrystal` e `Servo` já estão incluídas na IDE por padrão.
4. **Versão 7 Segmentos:** instale as bibliotecas `Adafruit LED Backpack` e `Adafruit GFX` pelo gerenciador de bibliotecas da IDE.
5. Monte o circuito conforme o esquema do simulador e faça o upload para a placa.
6. Abra o **Serial Monitor** em **9600 baud** para acompanhar os logs gerados a cada ação.