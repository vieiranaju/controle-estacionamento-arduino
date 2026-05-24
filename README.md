# Sistema de Controle de Estacionamento com Arduino

Este repositório contém o código de um sistema automatizado para um estacionamento universitário de 20 vagas. O projeto foi feito para a Avaliação 01 da disciplina de Sistemas Embarcados e possui duas versões: uma utilizando um display LCD e outra utilizando um display de 7 segmentos.

---

## 1. Versão com Display LCD (`estacionamento_lcd.ino`)

Nesta versão, as informações detalhadas sobre o estado do estacionamento aparecem na tela LCD, e o controle de abertura e fechamento da catraca é feito manualmente passo a passo.

### Como funciona
* **Entrada:** Um botão serve para registrar a entrada. Quando apertado, a catraca (representada pelo servo motor) se abre e o LED verde acende indicando passagem liberada.
* **Saída:** O outro botão serve para registrar a saída. Ele indica que o carro já passou, então a catraca fecha e o LED vermelho acende.
* **Tela:** O display LCD mostra as mensagens de status e a quantidade de vagas ainda disponíveis.
* **Lotação:** Se as 20 vagas estiverem ocupadas, o sistema não abre a catraca para novos carros e mostra um aviso de lotado na tela.

### Componentes Utilizados
* 1x Placa compatível com Arduino Uno
* 1x Servo Motor (simula a catraca)
* 1x Display LCD 16x2
* 1x Potenciômetro (necessário para controlar o contraste/iluminação da tela LCD)
* 2x Botões (um para abrir e outro para fechar)
* 1x LED Verde e 1x LED Vermelho
* Resistores de 220 Ω (para proteger os LEDs)
* Protoboard e Jumpers

### Link e Esquema do Circuito (LCD)
* [Acesse a simulação do projeto com LCD aqui](INSIRA_O_LINK_AQUI)

![Esquema do Circuito - Versão LCD](INSIRA_O_CAMINHO_DA_IMAGEM_AQUI)

---

## 2. Versão com Display de 7 Segmentos (`estacionamento_7seg.ino`)

Nesta segunda versão, o sistema foca em mostrar o número exato de vagas livres de forma direta e rápida através do display numérico de 7 segmentos, funcionando de uma forma um pouco mais automática.

### Como funciona
* **Entrada:** Um botão é usado para a entrada. Ao ser pressionado, o número de vagas na tela diminui e a catraca abre para o carro entrar, fechando sozinha depois de alguns segundos.
* **Saída:** O outro botão é usado para a saída. Quando pressionado, ele libera uma vaga, o número na tela aumenta, e a catraca também abre para o carro sair, fechando sozinha logo em seguida.
* **Tela:** O display de 7 segmentos serve exclusivamente para mostrar a quantidade atualizada de vagas livres.

### Componentes Utilizados
* 1x Placa compatível com Arduino Uno
* 1x Servo Motor (simula a catraca)
* 1x Display de 7 Segmentos I2C (Adafruit LED Backpack)
* 2x Botões (um de entrada e um de saída)
* 1x LED Verde e 1x LED Vermelho
* Resistores de 220 Ω (para proteger os LEDs)
* Protoboard e Jumpers

### Link e Esquema do Circuito (7 Segmentos)
* [Acesse a simulação do projeto com 7 Segmentos aqui](INSIRA_O_LINK_AQUI)

![Esquema do Circuito - Versão 7 Segmentos](INSIRA_O_CAMINHO_DA_IMAGEM_AQUI)

---

## Como rodar o código

1. Faça o download dos arquivos `.ino`.
2. Abra o arquivo desejado na Arduino IDE.
3. Se for testar a versão do LCD, não precisa baixar bibliotecas extras (a `LiquidCrystal` e a `Servo` já vêm na IDE).
4. Se for testar a versão de 7 Segmentos, instale a biblioteca `Adafruit LED Backpack` pelo gerenciador da IDE.
5. Conecte os componentes conforme a montagem do simulador e faça o upload para a placa.
6. Abra o Monitor Serial (9600 baud) para acompanhar o texto gerado por trás das ações.