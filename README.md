# microcontroladores

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


# Microcontrollers Laboratory

This repository contains practical projects and circuits developed for the Microcontrollers course in the Computer Engineering program at UFGD. The main goal of these documented practices is the application of embedded systems concepts using the Arduino architecture and hardware simulations.

## Project Index

Below are the laboratories included in this repository. Each directory contains its own C++ source code, the electronic wiring schematic, and detailed documentation of its operation.

* **[Traffic Light](./Sinal_de_transito):** A hybrid smart traffic light for vehicles and pedestrians, implementing non-blocking timing logic (`millis`) and hardware interrupts.
* **[PWM Control](./PWM):** Pulse Width Modulation (PWM) control system featuring runtime automatic potentiometer calibration and dead zone (hysteresis) logic.
* **[LCD Color (I2C)](./LCD_color):** Integration of a 16x2 LCD display using the I2C bus, synchronized with an RGB LED to provide visual feedback for system states.
* **[Electronic Voting Machine v1](./Vote):** A voting system structured as a finite state machine, operated by physical buttons (with software debounce filtering) and audio feedback.
* **[Electronic Voting Machine v2](./Vote_v2):** An upgraded version of the voting machine, introducing a 4x4 matrix keypad for input scanning, data validation, and a hidden administrator mode for vote tallying.

## Technologies and Tools
* **Platform:** Arduino Uno
* **Language:** C/C++
* **Simulator:** Autodesk Tinkercad
