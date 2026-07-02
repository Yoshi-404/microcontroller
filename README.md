# microcontroller

Este repositório reúne os projetos práticos e circuitos desenvolvidos para a disciplina de Microcontroladores do curso de Engenharia de Computação da UFGD. O objetivo principal das práticas documentadas aqui é a aplicação de conceitos de sistemas embarcados utilizando a arquitetura Arduino e simulações de hardware.

## Índice de Projetos

Abaixo estão os laboratórios contidos neste repositório. Cada diretório possui o seu próprio código-fonte em C++, o esquema de montagem eletrônica e uma documentação detalhada do funcionamento.

* **[Sinal de Trânsito](./Sinal_de_transito):** Semáforo inteligente e híbrido para veículos e pedestres, implementando lógicas de temporização não-bloqueante (`millis`) e interrupção.
* **[Controle PWM](./PWM):** Sistema de controle de modulação por largura de pulso (PWM) com calibração automática de potenciômetros em tempo de execução e zona morta (histerese).
* **[LCD Color (I2C)](./LCD_color):** Integração de display LCD 16x2 utilizando barramento I2C, sincronizado com o acionamento de um LED RGB para feedback visual de estados.
* **[Urna Eletrônica v1](./Vote):** Sistema de votação estruturado em máquina de estados, operado por botões físicos (com filtro de *debounce* por software) e feedback sonoro.
* **[Urna Eletrônica v2](./Vote_v2):** Versão aprimorada da urna, introduzindo varredura de entradas via teclado matricial 4x4, validação de dados e um modo oculto de administrador para apuração.

## Tecnologias e Ferramentas
* **Plataforma:** Arduino Uno
* **Linguagem:** C/C++
* **Simulador:** Autodesk Tinkercad
