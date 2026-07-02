#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const int PIN_PROXIMO   = 2;
const int PIN_ANTERIOR  = 3;
const int PIN_CONFIRMAR = 4;
const int PIN_BUZZER    = 8;

const int NUM_EQUIPES = 5;
String equipes[NUM_EQUIPES] = {
  "Equipe 1",
  "Equipe 2",
  "Equipe 3",
  "Equipe 4",
  "Equipe 5"
};
int votos[NUM_EQUIPES] = {0, 0, 0, 0, 0};

enum Estado {
  TELA_BOAS_VINDAS,
  SELECIONAR_EQUIPE,
  CONFIRMAR_VOTO,
  VOTO_REGISTRADO
};

Estado estadoAtual = TELA_BOAS_VINDAS;
int equipeAtual    = 0;
int equipeSelecionada = 0;

unsigned long ultimoTempoBtn[3] = {0, 0, 0};
const unsigned long DEBOUNCE_MS = 200;

bool leituraAnterior[3] = {HIGH, HIGH, HIGH};

unsigned long tempoTela = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_PROXIMO,   INPUT_PULLUP);
  pinMode(PIN_ANTERIOR,  INPUT_PULLUP);
  pinMode(PIN_CONFIRMAR, INPUT_PULLUP);
  pinMode(PIN_BUZZER,    OUTPUT);

  // Inicialização específica do Tinkercad
  lcd.begin(16, 2); 
  lcd.setBacklight(1); 

  mostrarBoasVindas();
  tempoTela = millis();
}

void loop() {
  if (estadoAtual == TELA_BOAS_VINDAS && millis() - tempoTela > 2000) {
    estadoAtual = SELECIONAR_EQUIPE;
    equipeAtual = 0;
    mostrarSelecao();
    return;
  }

  if (estadoAtual == VOTO_REGISTRADO && millis() - tempoTela > 2000) {
    estadoAtual = TELA_BOAS_VINDAS;
    mostrarBoasVindas();
    tempoTela = millis();
    return;
  }

  bool btnProximo   = lerBotao(0, PIN_PROXIMO);
  bool btnAnterior  = lerBotao(1, PIN_ANTERIOR);
  bool btnConfirmar = lerBotao(2, PIN_CONFIRMAR);

  switch (estadoAtual) {

    case SELECIONAR_EQUIPE:
      if (btnProximo) {
        equipeAtual = (equipeAtual + 1) % NUM_EQUIPES;
        mostrarSelecao();
        bip(50);
      }
      if (btnAnterior) {
        equipeAtual = (equipeAtual - 1 + NUM_EQUIPES) % NUM_EQUIPES;
        mostrarSelecao();
        bip(50);
      }
      if (btnConfirmar) {
        equipeSelecionada = equipeAtual;
        estadoAtual = CONFIRMAR_VOTO;
        mostrarConfirmacao();
        bip(80);
      }
      break;

    case CONFIRMAR_VOTO:
      if (btnConfirmar) {
        votos[equipeSelecionada]++;
        registrarVoto();
        estadoAtual = VOTO_REGISTRADO;
        tempoTela = millis();
        imprimirVotosSerial();
      }
      if (btnProximo) {
        equipeAtual = (equipeSelecionada + 1) % NUM_EQUIPES;
        estadoAtual = SELECIONAR_EQUIPE;
        mostrarSelecao();
        bip(50);
      }
      if (btnAnterior) {
        equipeAtual = (equipeSelecionada - 1 + NUM_EQUIPES) % NUM_EQUIPES;
        estadoAtual = SELECIONAR_EQUIPE;
        mostrarSelecao();
        bip(50);
      }
      break;

    default:
      break;
  }
}

bool lerBotao(int idx, int pino) {
  bool leitura = digitalRead(pino);
  if (leitura == LOW && leituraAnterior[idx] == HIGH) {
    if (millis() - ultimoTempoBtn[idx] > DEBOUNCE_MS) {
      ultimoTempoBtn[idx] = millis();
      leituraAnterior[idx] = LOW;
      return true;
    }
  }
  if (leitura == HIGH) {
    leituraAnterior[idx] = HIGH;
  }
  return false;
}

void mostrarBoasVindas() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("BEM-VINDO!");
  lcd.setCursor(1, 1);
  lcd.print("Escolha seu voto");
}

void mostrarSelecao() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(">> Vote em:");
  lcd.setCursor(0, 1);
  String nome = equipes[equipeAtual];
  if (nome.length() > 16) nome = nome.substring(0, 16);
  lcd.print(nome);
}

void mostrarConfirmacao() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Deseja confirmar");
  lcd.setCursor(0, 1);
  String nome = equipes[equipeSelecionada];
  if (nome.length() > 14) nome = nome.substring(0, 14);
  lcd.print("> ");
  lcd.print(nome);
}

void registrarVoto() {
  tone(PIN_BUZZER, 1046, 120); delay(130); 
  tone(PIN_BUZZER, 1318, 120); delay(130); 
  tone(PIN_BUZZER, 1568, 200); delay(220); 
  noTone(PIN_BUZZER);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("VOTO VALIDO!");
  lcd.setCursor(1, 1);
  lcd.print("Voto registrado!");
}

void bip(int duracao) {
  tone(PIN_BUZZER, 800, duracao);
}

void imprimirVotosSerial() {
  Serial.println("===== CONTAGEM DE VOTOS =====");
  int vencedor = 0;
  for (int i = 0; i < NUM_EQUIPES; i++) {
    Serial.print(equipes[i]);
    Serial.print(": ");
    Serial.print(votos[i]);
    Serial.println(" voto(s)");
    if (votos[i] > votos[vencedor]) vencedor = i;
  }
  Serial.print(">> Lider atual: ");
  Serial.println(equipes[vencedor]);
  Serial.println("=============================");
}