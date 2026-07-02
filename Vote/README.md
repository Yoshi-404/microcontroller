# Sistema de Votacao Eletronica com Interface LCD e Feedback Sonoro

Este projeto implementa uma urna eletronica simulada utilizando a plataforma Arduino[cite: 4]. O sistema permite a selecao e confirmacao de votos entre 5 equipes pre-definidas, exibindo a interface em um display LCD I2C e emitindo alertas sonoros atraves de um buzzer piezoeletrico[cite: 4].

## Funcionalidades e Logica de Controle

* **Maquina de Estados:** O fluxo principal do programa e estruturado atraves de uma maquina de estados finitos (`enum Estado`), transitando entre as telas de Boas-vindas, Selecao de Equipe, Confirmacao de Voto e Voto Registrado[cite: 4].
* **Navegacao e Tratamento de Sinais:** A navegacao entre as opcoes e realizada por botoes fisicos configurados como pull-up interno[cite: 4]. O codigo implementa uma rotina de software para *debounce* (filtro de ruido mecânico) de 200 milissegundos utilizando a funcao `millis()`, garantindo que leituras falsas nao contabilizem multiplos cliques[cite: 4].
* **Feedback Sonoro (Buzzer):** O sistema emite bipes curtos de 50 a 80 milissegundos ao navegar pelas opcoes ou solicitar confirmacao[cite: 4]. Ao confirmar um voto validamente, uma breve sequencia de notas musicais e reproduzida[cite: 4].
* **Contabilidade e Monitoramento Serial:** Um array armazena o numero de votos de cada uma das 5 equipes[cite: 4]. A cada voto confirmado, o microcontrolador transmite um relatorio atualizado da contagem e aponta o lider atual via Monitor Serial operando a 9600 bps[cite: 4].

## Pinagem e Conexoes

| Componente | Pino Arduino | Configuracao | Descricao |
| :--- | :---: | :---: | :--- |
| **Botao Proximo** | `Pin 2` | INPUT_PULLUP | Avanca para a proxima equipe na lista[cite: 4] |
| **Botao Anterior** | `Pin 3` | INPUT_PULLUP | Retorna para a equipe anterior na lista[cite: 4] |
| **Botao Confirmar** | `Pin 4` | INPUT_PULLUP | Seleciona e confirma o voto na equipe atual[cite: 4] |
| **Buzzer** | `Pin 8` | OUTPUT | Emissor de sinais sonoros utilizando a funcao `tone()`[cite: 4] |
| **LCD I2C (SDA)** | `A4` | I2C Data | Linha de dados para comunicacao com o display[cite: 4] |
| **LCD I2C (SCL)** | `A5` | I2C Clock | Linha de clock para comunicacao com o display[cite: 4] |

## Esquema do Circuito

Abaixo esta a disposicao dos componentes e conexoes do circuito projetado na plataforma Tinkercad:

![Circuito de Votacao Eletronica](vote.png)