//Projeto Microcontroladores - Semáforo de veículos e pedestre com parada e tempo automático

// Declarando variáveis de portas (Ajustadas para a montagem da imagem)
const int ledGreenCar = 8;   // Porta do Led Verde (Perna G do RGB) do semáforo dos carros 
const int ledYellowCar = 11; // Porta do Led Amarelo do semáforo dos carros 
const int ledRedCar = 10;    // Porta do Led Vermelho (Perna R do RGB) do semáforo dos carros 

const int ledGreenPed = 7;   // Porta do Led Verde do semáforo dos pedestres 
const int ledRedPed = 5;     // Porta do Led Vermelho do semáforo dos pedestres 

const int botPed = 2;        // Porta do botão do semáforo dos pedestres 

// Declarando variáveis de tempo
unsigned long tempo;         
const unsigned long tempoMinimoVerde = 5000;  // 5s: Tempo mínimo de verde para os carros antes do botão funcionar
const unsigned long tempoMaximoVerde = 10000; // 10s: Tempo para o semáforo rodar sozinho (modo automático)

void setup()
{
  tempo = millis(); // Atribui à variável tempo o valor do início do programa
  
  pinMode(ledGreenCar, OUTPUT);   
  pinMode(ledYellowCar, OUTPUT);  
  pinMode(ledRedCar, OUTPUT);     
  
  pinMode(ledGreenPed, OUTPUT);   
  pinMode(ledRedPed, OUTPUT);     
  
  pinMode(botPed, INPUT_PULLUP);  // Define a porta 2 como entrada com Resistor de Pull Up interno

  digitalWrite(ledGreenCar, 1);   // Inicia com a luz Verde do semáforo dos carros
  digitalWrite(ledRedPed, 1);     // Inicia com a luz Vermelha do semáforo dos pedestres
}

void loop(){
  int leitura = digitalRead(botPed); 
  unsigned long tempoDecorrido = millis() - tempo; // Calcula quanto tempo o sinal está verde para os carros
  
  // Condição 1: Botão foi apertado E o sinal dos carros já está verde há pelo menos 5 segundos
  bool ativadoPorBotao = (leitura == 0 && tempoDecorrido > tempoMinimoVerde);
  
  // Condição 2: Ninguém apertou o botão, mas o tempo máximo do verde (15 segundos) estourou
  bool ativadoPorTempo = (tempoDecorrido > tempoMaximoVerde);

  // Se qualquer uma das duas condições for verdadeira, roda o ciclo do semáforo
  if(ativadoPorBotao || ativadoPorTempo){ 
      
      digitalWrite(ledGreenCar, 0);   // Apaga a luz verde do semáforo dos carros
      digitalWrite(ledYellowCar, 1);  // Acende a luz amarela do semáforo dos carros
      delay(2000);                    // Espera de 2 segundos do amarelo
      
      digitalWrite(ledYellowCar, 0);  // Apaga a luz amarela do semáforo dos carros
      digitalWrite(ledRedCar, 1);     // Acende a luz vermelha do semáforo dos carros
      delay(1000);                    // Espera de 1 segundo de segurança
      
      digitalWrite(ledRedPed, 0);     // Apaga a luz vermelha do semáforo dos pedestres
      digitalWrite(ledGreenPed, 1);   // Acende a luz verde do semáforo dos pedestres
      delay(5000);                    // Tempo de travessia do pedestre (5 segundos)
      
      for(int i = 0 ; i < 5 ; i++){   // Comando para fazer a luz verde dos pedestres piscar
        digitalWrite(ledGreenPed, 0); // Apaga a luz verde
        delay(500);                   
        digitalWrite(ledGreenPed, 1); // Acende a luz verde
        delay(500);                   
      }      
      digitalWrite(ledGreenPed, 0);   // Apaga a luz verde do semáforo dos pedestres  
      digitalWrite(ledRedPed, 1);     // Acende a luz vermelha do semáforo dos pedestres
      
      delay(500);                     // Espera de 0,5 segundos de segurança
      
      digitalWrite(ledRedCar, 0);     // Apaga a luz vermelha do semáforo dos carros
      digitalWrite(ledGreenCar, 1);   // Acende a luz verde do semáforo dos carros
            
      tempo = millis();               // Zera o cronômetro para iniciar um novo ciclo
  }
  
  delay(10); // Pequeno atraso para estabilidade do simulador/placa
}