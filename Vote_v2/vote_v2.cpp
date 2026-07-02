#include <Keypad.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

const byte LINHAS = 4;
const byte COLUNAS = 4;
char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS] = {13, 12, 11, 10}; 
byte pinosColunas[COLUNAS] = {9, 8, 7, 6}; 
Keypad teclado = Keypad(makeKeymap(teclas), pinosLinhas, pinosColunas, LINHAS, COLUNAS);

const int PINO_LED_R = 5;
const int PINO_LED_G = 4;
const int PINO_LED_B = 3;
const int PINO_BUZZER = 2;

String bufferDigitacao = "";
bool modoAdministrador = false;

int votosCand10 = 0;
int votosCand20 = 0;
int votosBrancosNulos = 0;

unsigned long tempoMensagem = 0;
bool exibindoMensagem = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  
  pinMode(PINO_LED_R, OUTPUT);
  pinMode(PINO_LED_G, OUTPUT);
  pinMode(PINO_LED_B, OUTPUT);
  pinMode(PINO_BUZZER, OUTPUT);
  
  apagarLED();
  mostrarTelaInicial();
}

void loop() {
  if (exibindoMensagem && millis() - tempoMensagem > 2000) {
    exibindoMensagem = false;
    apagarLED();
    mostrarTelaInicial();
  }

  char tecla = teclado.getKey();

  if (tecla && !exibindoMensagem) {
    bipCurto(); // Feedback sonoro imediato ao teclar
    
    if (modoAdministrador) {
      if (tecla == 'C') {
        modoAdministrador = false;
        bufferDigitacao = "";
        apagarLED();
        mostrarTelaInicial();
      }
      return;
    }

    switch (tecla) {
      case 'A':
        processarConfirmacao();
        break;
        
      case 'B':
        if (bufferDigitacao.length() > 0) {
          bufferDigitacao.remove(bufferDigitacao.length() - 1);
          atualizarDisplayDigitacao();
        }
        break;
        
      case 'C':
        bufferDigitacao = "";
        atualizarDisplayDigitacao();
        break;
        
      case 'D':
        votosBrancosNulos++;
        confirmarVotoStatus();
        break;
        
      default:
        if (bufferDigitacao.length() < 6) {
          bufferDigitacao += tecla;
          atualizarDisplayDigitacao();
        }
        break;
    }
  }
}

void processarConfirmacao() {
  if (bufferDigitacao == "*#*#") {
    modoAdministrador = true;
    bufferDigitacao = "";
    exibirModoAdministrador();
    return;
  }
  
  // Condição para os candidatos configurados
  if (bufferDigitacao == "10") {
    votosCand10++;
    confirmarVotoStatus();
  } else if (bufferDigitacao == "20") {
    votosCand20++;
    confirmarVotoStatus();
  } else {
    erroVotoStatus();
  }
}

void atualizarDisplayDigitacao() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Numero:");
  lcd.setCursor(0, 1);
  lcd.print(bufferDigitacao);
}

void mostrarTelaInicial() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("URNA ELETRONICA");
  lcd.setCursor(0, 1);
  lcd.print("Digite seu voto");
}

void confirmarVotoStatus() {
  acionarLED(0, 255, 0); // Pisca Verde
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FIM");
  lcd.setCursor(0, 1);
  lcd.print("Voto Registrado");
  
  somSucesso(); // Toca a melodia de fim de voto
  
  bufferDigitacao = "";
  exibindoMensagem = true;
  tempoMensagem = millis();
}

void erroVotoStatus() {
  acionarLED(255, 0, 0); // Pisca Vermelho
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NUMERO INVALIDO");
  lcd.setCursor(0, 1);
  lcd.print("C para limpar");
  
  somErro(); // Toca o som grave de erro
  
  exibindoMensagem = true;
  tempoMensagem = millis();
}

void exibirModoAdministrador() {
  acionarLED(0, 0, 255); // Pisca Azul
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("C10:");
  lcd.print(votosCand10);
  lcd.print(" C20:");
  lcd.print(votosCand20);
  
  lcd.setCursor(0, 1);
  lcd.print("Nul/Brc: ");
  lcd.print(votosBrancosNulos);
  
  somAdmin(); // Toca os bips duplos de administrador
}

// --- Funções de Controle Visual (LED RGB) ---
void acionarLED(int r, int g, int b) {
  analogWrite(PINO_LED_R, r);
  analogWrite(PINO_LED_G, g);
  analogWrite(PINO_LED_B, b);
}

void apagarLED() {
  acionarLED(0, 0, 0);
}

// --- Funções de Controle Sonoro (Buzzer) ---
void bipCurto() {
  tone(PINO_BUZZER, 800, 50);
}

void somSucesso() {
  // Mantida a melodia agradável da sua versão anterior
  tone(PINO_BUZZER, 1046, 120); delay(130); 
  tone(PINO_BUZZER, 1318, 120); delay(130); 
  tone(PINO_BUZZER, 1568, 200); delay(220); 
  noTone(PINO_BUZZER);
}

void somErro() {
  // Som mais grave e longo indicando falha
  tone(PINO_BUZZER, 250, 400); 
  delay(450);
  noTone(PINO_BUZZER);
}

void somAdmin() {
  // Dois bips agudos rápidos para mudança de contexto
  tone(PINO_BUZZER, 2000, 100); delay(150);
  tone(PINO_BUZZER, 2000, 100); delay(150);
  noTone(PINO_BUZZER);
}