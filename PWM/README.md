# Sistema de Controle PWM com Calibração Automática

Este projeto implementa um sistema avançado de controle de sinal PWM utilizando a plataforma Arduino[cite: 2]. O sistema destaca-se por possuir ajuste independente de incremento e decremento, além de um modo de calibração automática de hardware[cite: 2].

## Funcionalidades e Lógica de Controle

* **Controle Duplo:** O sistema utiliza dois potenciômetros distintos: um dedicado a aumentar o valor do PWM e outro para diminuí-lo[cite: 2]. O mapeamento inclui uma constante de zona morta para evitar instabilidades e ruídos nas leituras[cite: 2].
* **Botão Multifuncional:** O sistema possui um botão de controle no pino 2 que detecta a duração da pressão (clique curto ou longo) utilizando a função `millis()`[cite: 2]. Um clique curto ativa ou desativa o sistema (alternando para o modo standby)[cite: 2]. Um clique longo (3 segundos ou mais) inicia a rotina de calibração dos potenciômetros[cite: 2].
* **Calibração Automática:** Durante um intervalo de 5 segundos, o usuário deve girar os potenciômetros para que o sistema registre os valores mínimos e máximos reais[cite: 2]. Isso garante maior precisão na conversão dos sinais analógicos[cite: 2].
* **Feedback Visual (LED RGB):** O estado de operação do sistema é reportado continuamente através de um LED RGB[cite: 2]. A cor azul fixa indica que o sistema está em modo standby[cite: 2]. A cor verde acende com intensidade proporcional ao aumentar o valor do PWM[cite: 2]. A cor vermelha acende de forma proporcional ao diminuir o valor do PWM[cite: 2]. A cor roxa piscando indica que o modo de calibração está em andamento[cite: 2].
* **Monitoramento Serial:** As alterações no valor de PWM, as leituras dos sensores e o status da calibração são enviados para o monitor serial operando a 9600 bps[cite: 2].

## Pinagem e Conexões

| Componente | Pino Arduino | Configuração | Descrição |
| :--- | :---: | :---: | :--- |
| **Potenciômetro Aumento** | `A0` | ANALOG IN | Lê o sinal analógico para incrementar o PWM[cite: 2] |
| **Potenciômetro Diminuição** | `A1` | ANALOG IN | Lê o sinal analógico para decrementar o PWM[cite: 2] |
| **LED RGB (Vermelho)** | `Pin 9` | OUTPUT | Controle do canal vermelho do LED de feedback[cite: 2] |
| **LED RGB (Verde)** | `Pin 10` | OUTPUT | Controle do canal verde do LED de feedback[cite: 2] |
| **LED RGB (Azul)** | `Pin 11` | OUTPUT | Controle do canal azul do LED de feedback[cite: 2] |
| **Saída PWM Principal** | `Pin 5` | OUTPUT | Saída final do sinal PWM para o circuito controlado[cite: 2] |
| **Botão de Controle** | `Pin 2` | INPUT_PULLUP | Botão multifunção utilizando o resistor de pull-up interno[cite: 2] |

## Esquema do Circuito

Abaixo está a disposição dos componentes montados e simulados na plataforma Tinkercad:

![Circuito de Controle PWM](PWM.png)