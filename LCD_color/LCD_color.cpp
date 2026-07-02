#include <LiquidCrystal_I2C.h>

#include <Adafruit_LiquidCrystal.h>

// Inicializa o LCD I2C no Tinkercad (O endereço padrão no simulador costuma ser 0)
Adafruit_LiquidCrystal lcd(0);

// Configuração dos pinos do LED RGB
int pinoVermelho = 9;
int pinoVerde = 10;
int pinoAzul = 11;

void setup() {
  // Inicializa o LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
  
  // Liga a luz de fundo do LCD I2C
  lcd.setBacklight(1);
  
  lcd.print("Sistema I2C OK");
  
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
  pinMode(pinoAzul, OUTPUT);
  
  delay(2000);
}

void loop() {
  lcd.clear();
  lcd.print("Cor:");
  lcd.setCursor(0, 1);
  lcd.print("-> VERMELHO");
  definirCorRGB(255, 0, 0); 
  delay(2000);

  lcd.clear();
  lcd.print("Cor:");
  lcd.setCursor(0, 1);
  lcd.print("-> VERDE");
  definirCorRGB(0, 255, 0); 
  delay(2000);

  lcd.clear();
  lcd.print("Cor:");
  lcd.setCursor(0, 1);
  lcd.print("-> AZUL");
  definirCorRGB(0, 0, 255); 
  delay(2000);
}

void definirCorRGB(int valorVermelho, int valorVerde, int valorAzul) {
  analogWrite(pinoVermelho, valorVermelho);
  analogWrite(pinoVerde, valorVerde);
  analogWrite(pinoAzul, valorAzul);
}
