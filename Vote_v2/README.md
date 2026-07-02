# Urna Eletronica v2: Teclado Matricial, Display I2C e Modo Administrador

Este projeto consiste em uma versao aprimorada de um sistema de votacao eletronica baseado em Arduino[cite: 5]. O circuito foi atualizado para utilizar um teclado matricial 4x4 para a entrada de dados, mantendo o display LCD via I2C para interface e adicionando um LED RGB em conjunto com um buzzer para feedback multissensorial[cite: 5].

## Funcionalidades e Logica de Sistema

* **Interface de Teclado Matricial:** A entrada de dados e gerenciada pela biblioteca `Keypad.h`, mapeando as linhas e colunas para pinos digitais do Arduino[cite: 5]. O mapeamento de funcoes e o seguinte:
  * **Teclas 0-9:** Insercao do numero do candidato[cite: 5].
  * **Tecla A:** Confirmacao do voto digitado[cite: 5].
  * **Tecla B:** Apaga o ultimo digito inserido (Backspace)[cite: 5].
  * **Tecla C:** Limpa completamente o buffer de digitacao[cite: 5].
  * **Tecla D:** Computa um voto Branco/Nulo[cite: 5].
* **Validacao de Votos:** O sistema valida a entrada contra dois candidatos pre-configurados (numeros "10" e "20")[cite: 5]. Se um numero invalido for confirmado, o sistema bloqueia a tela momentaneamente e emite um aviso de erro[cite: 5].
* **Modo Administrador (Secret Code):** Existe um fluxo oculto para contabilizacao[cite: 5]. Ao digitar a sequencia `*#*#` e pressionar confirmar (`A`), o sistema entra em Modo Administrador, exibindo no display o total de votos de cada candidato e os votos brancos/nulos[cite: 5].
* **Feedback Multissensorial:**
  * **Visual (LED RGB):** Pisca em Verde para voto registrado com sucesso, Vermelho para numero invalido e Azul ao entrar no modo administrador[cite: 5].
  * **Sonoro (Buzzer):** Emite um bipe curto a cada tecla pressionada, uma melodia de sucesso ao confirmar o voto, um bipe grave e longo para erros, e um bipe duplo agudo ao acessar o painel de administrador[cite: 5].

## Pinagem e Conexoes

| Componente | Pino Arduino | Configuracao | Descricao |
| :--- | :---: | :---: | :--- |
| **Teclado (Linhas)** | `13, 12, 11, 10` | INPUT_PULLUP (via lib) | Pinos referentes as 4 linhas do teclado matricial[cite: 5] |
| **Teclado (Colunas)** | `9, 8, 7, 6` | OUTPUT (via lib) | Pinos referentes as 4 colunas do teclado matricial[cite: 5] |
| **LED RGB (Vermelho)** | `Pin 5` | OUTPUT | Sinal PWM para o canal vermelho[cite: 5] |
| **LED RGB (Verde)** | `Pin 4` | OUTPUT | Sinal PWM para o canal verde[cite: 5] |
| **LED RGB (Azul)** | `Pin 3` | OUTPUT | Sinal PWM para o canal azul[cite: 5] |
| **Buzzer** | `Pin 2` | OUTPUT | Emissor sonoro controlado pela funcao `tone()`[cite: 5] |
| **LCD I2C (SDA)** | `A4` | I2C Data | Linha de dados do barramento I2C[cite: 5] |
| **LCD I2C (SCL)** | `A5` | I2C Clock | Linha de clock do barramento I2C[cite: 5] |

## Esquema do Circuito

Abaixo esta a disposicao dos componentes e cabeamento projetados na plataforma Tinkercad:

![Circuito Urna Eletronica v2](vote_v2.png)