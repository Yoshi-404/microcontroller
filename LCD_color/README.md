# Display LCD I2C e Sincronização de LED RGB

Este projeto demonstra a integração de um display LCD de 16x2 utilizando comunicação I2C em conjunto com o controle de um LED RGB no Arduino[cite: 3]. O sistema sincroniza a informação visual de texto do display com a mudança de cores físicas do componente luminoso[cite: 3].

## Funcionalidades e Lógica

* **Comunicação I2C:** O projeto utiliza a biblioteca `Adafruit_LiquidCrystal.h` para gerenciar o display através do barramento I2C (endereço 0 no simulador Tinkercad), o que poupa portas digitais do Arduino[cite: 3].
* **Inicialização:** Durante o `setup()`, a luz de fundo do LCD é ativada e a mensagem de validação "Sistema I2C OK" é exibida por 2 segundos[cite: 3].
* **Ciclo de Cores:** No loop principal, o sistema alterna automaticamente entre três estados com intervalos de 2 segundos cada[cite: 3].
* **Sincronização de Feedback:** A cada mudança de estado, o display é limpo e atualizado para exibir "Cor:" na primeira linha, seguido da indicação da cor atual (ex: "-> VERMELHO", "-> VERDE" ou "-> AZUL") na segunda linha[cite: 3].
* **Modularização:** O código conta com uma função dedicada `definirCorRGB(int valorVermelho, int valorVerde, int valorAzul)` que recebe os parâmetros de intensidade e aplica o sinal via `analogWrite` nos pinos correspondentes[cite: 3].

## Pinagem e Conexões

| Componente | Pino Arduino | Configuração | Descrição |
| :--- | :---: | :---: | :--- |
| **LED RGB (Vermelho)** | `Pin 9` | OUTPUT | Controla o canal vermelho (R) via sinal PWM[cite: 3] |
| **LED RGB (Verde)** | `Pin 10` | OUTPUT | Controla o canal verde (G) via sinal PWM[cite: 3] |
| **LED RGB (Azul)** | `Pin 11` | OUTPUT | Controla o canal azul (B) via sinal PWM[cite: 3] |
| **LCD I2C (SDA)** | `A4` | I2C Data | Linha de dados do barramento I2C |
| **LCD I2C (SCL)** | `A5` | I2C Clock | Linha de clock do barramento I2C |

## Esquema do Circuito

Abaixo está a disposição dos componentes e das conexões I2C simuladas através da plataforma Tinkercad:

![Circuito LCD e RGB no Tinkercad](LCD_color.png)