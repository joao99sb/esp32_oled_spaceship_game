#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels'

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 4
#define BUTTON_PIN_3 19

#define OLED_ADDRESS 0x3C
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

#define BOTAO_PIN 4 // Pino ao qual o botão está conectado

// Bitmap do foguete (exemplo simples)
const uint8_t foguete_bitmap[] = {
    0b0000000,
    0b0001100,
    0b0001110,
    0b0111111,
    0b1111111,
    0b0111111,
    0b0001110,
    0b0001100,
};

int posicaoYFoguete = SCREEN_HEIGHT / 2; // Posição inicial do foguete

void setup()
{
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  { // Endereço 0x3C para displays com 128x64 pixels
    Serial.println(F("Falha ao iniciar o display OLED"));
    for (;;)
      ; // Não faça nada se falhar
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  pinMode(BUTTON_PIN_1, INPUT); // Configura o pino do botão de subir como entrada com pull-up interno
  pinMode(BUTTON_PIN_2, INPUT); // Configura o pino do botão de descer como entrada com pull-up interno
  pinMode(BUTTON_PIN_3, INPUT); // Configura o pino do botão de descer como entrada com pull-up interno
}

void loop()
{
  int upBtnState = digitalRead(2);
  int downBtnState = digitalRead(4);
  int laserState = digitalRead(19);

  if (upBtnState == HIGH)
  { // Se o botão de subir estiver pressionado
    posicaoYFoguete -= 5;
    if (posicaoYFoguete < 0)
    {
      posicaoYFoguete = 0; // Limita a posição mínima do foguete
    }
  }
  else if (downBtnState == HIGH)
  { // Se o botão de descer estiver pressionado
    posicaoYFoguete += 5;
    if (posicaoYFoguete > SCREEN_HEIGHT - 8)
    {                                      // 8 é a altura do bitmap do foguete
      posicaoYFoguete = SCREEN_HEIGHT - 8; // Limita a posição máxima do foguete
    }
    display.drawLine(40, posicaoYFoguete + 4, 40, 0, WHITE); 
  }

  display.clearDisplay();
  display.drawBitmap(0, posicaoYFoguete, foguete_bitmap, 8, 8, WHITE); // Desenha o foguete na posição atualizada

  if (laserState == HIGH)
  {                                     // Se o botão de disparar laser estiver pressionado
    int xInicial = SCREEN_WIDTH / 5;    // Centraliza o laser na tela
    int yInicial = posicaoYFoguete + 4; // Começa do centro do foguete
    int comprimentoLaser = 20;          // Define o comprimento do laser
    display.drawFastHLine(xInicial, yInicial, comprimentoLaser, WHITE);
  }

  display.display();
  delay(10);
}