# Urna Eletronica v2: Teclado Matricial, Display I2C e Modo Administrador

Este projeto consiste em uma versao aprimorada de um sistema de votacao eletronica baseado em Arduino. O circuito foi atualizado para utilizar um teclado matricial 4x4 para a entrada de dados, mantendo o display LCD via I2C para interface e adicionando um LED RGB em conjunto com um buzzer para feedback multissensorial.

## Funcionalidades e Logica de Sistema

* **Interface de Teclado Matricial:** A entrada de dados e gerenciada pela biblioteca `Keypad.h`, mapeando as linhas e colunas para pinos digitais do Arduino. O mapeamento de funcoes e o seguinte:
  * **Teclas 0-9:** Insercao do numero do candidato.
  * **Tecla A:** Confirmacao do voto digitado.
  * **Tecla B:** Apaga o ultimo digito inserido (Backspace).
  * **Tecla C:** Limpa completamente o buffer de digitacao.
  * **Tecla D:** Computa um voto Branco/Nulo.
* **Validacao de Votos:** O sistema valida a entrada contra dois candidatos pre-configurados (numeros "10" e "20"). Se um numero invalido for confirmado, o sistema bloqueia a tela momentaneamente e emite um aviso de erro.
* **Modo Administrador (Secret Code):** Existe um fluxo oculto para contabilizacao. Ao digitar a sequencia `*#*#` e pressionar confirmar (`A`), o sistema entra em Modo Administrador, exibindo no display o total de votos de cada candidato e os votos brancos/nulos.
* **Feedback Multissensorial:**
  * **Visual (LED RGB):** Pisca em Verde para voto registrado com sucesso, Vermelho para numero invalido e Azul ao entrar no modo administrador.
  * **Sonoro (Buzzer):** Emite um bipe curto a cada tecla pressionada, uma melodia de sucesso ao confirmar o voto, um bipe grave e longo para erros, e um bipe duplo agudo ao acessar o painel de administrador.

## Pinagem e Conexoes

| Componente | Pino Arduino | Configuracao | Descricao |
| :--- | :---: | :---: | :--- |
| **Teclado (Linhas)** | `13, 12, 11, 10` | INPUT_PULLUP (via lib) | Pinos referentes as 4 linhas do teclado matricial |
| **Teclado (Colunas)** | `9, 8, 7, 6` | OUTPUT (via lib) | Pinos referentes as 4 colunas do teclado matricial |
| **LED RGB (Vermelho)** | `Pin 5` | OUTPUT | Sinal PWM para o canal vermelho |
| **LED RGB (Verde)** | `Pin 4` | OUTPUT | Sinal PWM para o canal verde |
| **LED RGB (Azul)** | `Pin 3` | OUTPUT | Sinal PWM para o canal azul |
| **Buzzer** | `Pin 2` | OUTPUT | Emissor sonoro controlado pela funcao `tone()` |
| **LCD I2C (SDA)** | `A4` | I2C Data | Linha de dados do barramento I2C |
| **LCD I2C (SCL)** | `A5` | I2C Clock | Linha de clock do barramento I2C |

## Esquema do Circuito

Abaixo esta a disposicao dos componentes e cabeamento projetados na plataforma Tinkercad:

![Circuito Urna Eletronica v2](vote_v2.png)
