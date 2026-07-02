// Componentes

// Potenciometros
const int potAumenta = A0;
const int potDiminui = A1;

// RGB
const int ledR = 9;
const int ledG = 10;
const int ledB = 11;

// PWM principal
const int pwmPin = 5;

// Botao
const int botao = 2;

// Variáveis de valor

// Valor do PWM
int pwmValue = 0;

// Estado do sistema
bool sistemaAtivo = true;

// Controle do botao
bool botaoPressionado = false;

unsigned long tempoBotao = 0;

// Calibraçãi

// Valores minimos e maximos detectados

int minPotA = 1023;
int maxPotA = 0;

int minPotD = 1023;
int maxPotD = 0;

// Histerese

// Zona morta contra ruido

const int zonaMorta = 3;

void setup() {

  // RGB
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  // PWM
  pinMode(pwmPin, OUTPUT);

  // Botao
  pinMode(botao, INPUT_PULLUP);

  // Serial
  Serial.begin(9600);

  Serial.println("Sistema iniciado");

  // Inicializa limites padrao
  minPotA = 0;
  maxPotA = 1023;

  minPotD = 0;
  maxPotD = 1023;

  // RGB inicial
  setColor(0, 0, 0);
}

void loop() {

  verificarBotao();

  // Sistema desligado

  if (!sistemaAtivo) {

    analogWrite(pwmPin, 0);

    // Azul = standby
    setColor(0, 0, 255);

    return;
  }

  controlarPWM();

  // Atualiza PWM principal
  analogWrite(pwmPin, pwmValue);

  delay(40);
}

// Controle PWM

void controlarPWM() {

  int leituraA = analogRead(potAumenta);
  int leituraD = analogRead(potDiminui);

  // Aplica limites calibrados

  leituraA = constrain(leituraA, minPotA, maxPotA);
  leituraD = constrain(leituraD, minPotD, maxPotD);

  // Converte valores

  int aumento = map(leituraA,
                    minPotA,
                    maxPotA,
                    0,
                    10);

  int diminuicao = map(leituraD,
                       minPotD,
                       maxPotD,
                       0,
                       10);

  bool alterou = false;

  // Aumentar PWM

  if (aumento > zonaMorta) {

    pwmValue += aumento;

    // Limita PWM
    pwmValue = constrain(pwmValue, 0, 255);

    // Verde proporcional ao PWM
    setColor(0, pwmValue, 0);

    alterou = true;
  }

  // Diminuir PWM

  else if (diminuicao > zonaMorta) {

    pwmValue -= diminuicao;

    // Limita PWM
    pwmValue = constrain(pwmValue, 0, 255);

    // Vermelho proporcional ao PWM
    setColor(pwmValue, 0, 0);

    alterou = true;
  }

// Sem alteração

  else {

    // RGB apagado
    setColor(0, 0, 0);
  }

// Serial

  if (alterou) {

    Serial.print("PWM: ");
    Serial.print(pwmValue);

    Serial.print(" | POT+: ");
    Serial.print(leituraA);

    Serial.print(" | POT-: ");
    Serial.println(leituraD);
  }
}

// Verificar botão

void verificarBotao() {

  // INPUT_PULLUP
  bool estadoBotao = !digitalRead(botao);

  // Botão pressionado

  if (estadoBotao && !botaoPressionado) {

    botaoPressionado = true;

    tempoBotao = millis();
  }

  // Botão solto

  if (!estadoBotao && botaoPressionado) {

    unsigned long tempoPressionado =
      millis() - tempoBotao;

    botaoPressionado = false;

    // Clique longo ->

    if (tempoPressionado >= 3000) {

      calibrarPotenciometros();
    }

    // Clique curto -> on/off

    else {

      sistemaAtivo = !sistemaAtivo;

      Serial.print("Sistema ");

      if (sistemaAtivo) {

        Serial.println("ATIVADO");

      } else {

        Serial.println("DESATIVADO");
      }
    }
  }
}

// Calibração automática

void calibrarPotenciometros() {

  Serial.println("\n==========================");
  Serial.println("MODO CALIBRACAO");
  Serial.println("Gire os potenciometros");
  Serial.println("Tempo: 5 segundos");
  Serial.println("==========================");

  // Reinicia limites

  minPotA = 1023;
  maxPotA = 0;

  minPotD = 1023;
  maxPotD = 0;

  unsigned long inicio = millis();

  // Leitura dos limites

  while (millis() - inicio < 5000) {

    int leituraA = analogRead(potAumenta);
    int leituraD = analogRead(potDiminui);

    // Pot aumento

    if (leituraA < minPotA) {
      minPotA = leituraA;
    }

    if (leituraA > maxPotA) {
      maxPotA = leituraA;
    }

    // pot diminuição
    if (leituraD < minPotD) {
      minPotD = leituraD;
    }

    if (leituraD > maxPotD) {
      maxPotD = leituraD;
    }

    // RGB roxo piscando

    setColor(255, 0, 255);
    delay(120);

    setColor(0, 0, 0);
    delay(120);
  }

  // Segyurança

  // Evita faixa muito pequena

  if ((maxPotA - minPotA) < 50) {

    minPotA = 0;
    maxPotA = 1023;
  }

  if ((maxPotD - minPotD) < 50) {

    minPotD = 0;
    maxPotD = 1023;
  }

  // Resultados

  Serial.println("\nCALIBRACAO FINALIZADA");

  Serial.print("POT+ MIN: ");
  Serial.print(minPotA);

  Serial.print(" | MAX: ");
  Serial.println(maxPotA);

  Serial.print("POT- MIN: ");
  Serial.print(minPotD);

  Serial.print(" | MAX: ");
  Serial.println(maxPotD);

  Serial.println("==========================\n");

  // Apaga RGB
  setColor(0, 0, 0);
}

// Controle RGB

void setColor(int r, int g, int b) {

  // RGB catodo comum

  analogWrite(ledR, r);
  analogWrite(ledG, g);
  analogWrite(ledB, b);
}