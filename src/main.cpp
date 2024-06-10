#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "../include/matrix.h"
#include "../include/menu.h"
#include "../include/spaceship.h"
#include "../include/buffer.h"
#include "../include/staticEntity.h"

#define SCREEN_WIDTH 128 // Largura da tela em pixels
#define SCREEN_HEIGHT 64 // Altura da tela em pixels

#define OLED_RESET -1 // RST não conectado
#define OLED_ADDRESS 0x3C

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 4
#define BUTTON_PIN_3 19

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Buffer que representa a tela
#define BUFFER_HEIGHT SCREEN_HEIGHT - MENU_HEIGHT

#define GAME_BUFFER_START MENU_HEIGHT
Buffer *gameBuffer;

void updateDisplayFromBuffer(Buffer *buffer)
{
  // Limpa o buffer do display

  for (int y = 0; y < SCREEN_HEIGHT; y++)
  {
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
      if (buffer->getMatrixValue(y, x) == 1)
      {
        display.drawPixel(x, y, WHITE); // Desenha um pixel branco na posição (x, y)
      }
    }
  }
}

#define SPACE_WIDTH 6
#define SPACE_HEIGHT 11

int spaceship_x_pos = 1;                                                // Posição X inicial da imagem
int spaceship_y_pos = (SCREEN_HEIGHT / 2) - MENU_HEIGHT;                // Posição Y inicial da imagem
int spaceship_max_y_pos = SCREEN_HEIGHT - (MENU_HEIGHT + SPACE_HEIGHT); // Posição Y inicial da imagem
Spaceship *spaceship;

typedef struct
{
  StaticEntity *blok;
  int laser_timer;
  bool is_laser_able;
} Laser;
Laser laser;
Buffer *menu;

void setupMenu()
{
  display.setTextSize(1);      // Tamanho do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0, 0);     // Posição inicial do texto (x, y)

  // Exibe "Hello, world!" na tela
  display.println("Hello, world!");
}
void setup()
{
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Não faça nada se falhar
  }

  // button setup
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);

  display.clearDisplay(); // Limpa o buffer do display

  // Inicializa o buffer com zeros
  // buffer = new Matrix(BUFFER_HEIGHT, SCREEN_WIDTH);
  gameBuffer = new Buffer(SCREEN_HEIGHT, SCREEN_WIDTH);
  gameBuffer->populateMatrix(0);
  menu = new Buffer(MENU_HEIGHT, SCREEN_WIDTH);
  menu->populateMatrix(1);

  spaceship = new Spaceship(SPACE_HEIGHT, SPACE_WIDTH,
                            spaceship_y_pos, spaceship_x_pos,
                            spaceship_max_y_pos, SCREEN_WIDTH,
                            1, 1);
  laser.blok = new StaticEntity(1, 10, spaceship_y_pos, 20);
  laser.blok->populateMatrix(1);
  laser.is_laser_able = true;
  laser.laser_timer = 10;

  Serial.println(spaceship_max_y_pos);
}

void loop()
{
  gameBuffer->resetBuffer();
  // laser->populateMatrix(0);

  // draw menu
  // drawImageFromMatrix(menu, 0, 0);

  int up_btn_state = digitalRead(BUTTON_PIN_1);
  int down_btn_state = digitalRead(BUTTON_PIN_2);
  int laser_btn_state = digitalRead(BUTTON_PIN_3);

  if (up_btn_state == HIGH)
  {
    spaceship->moveUp();
  }
  if (down_btn_state == HIGH)
  {
    spaceship->moveDown();
  }

  if (laser_btn_state == HIGH && laser.is_laser_able)
  {

    laser.blok->setCurrentX(SCREEN_WIDTH / 5);

    int spaceship_center_position = spaceship->getCurrentY() + spaceship->getHeight() / 2;
    laser.blok->setCurrentY(spaceship_center_position); // Começa do centro do foguete
    gameBuffer->drawImageFromMatrix(laser.blok, laser.blok->getCurrentY() + GAME_BUFFER_START, 20);

    laser.is_laser_able = false;
  }

  if (!laser.is_laser_able)
  {
    laser.laser_timer--;
    if (laser.laser_timer == 0)
    {
      laser.is_laser_able = true;
      laser.laser_timer = 10;
    }
  }

  // draw image
  gameBuffer->drawImageFromMatrix(spaceship, spaceship->getCurrentY() + MENU_HEIGHT, 0);
  display.clearDisplay();
  updateDisplayFromBuffer(gameBuffer);
  updateDisplayFromBuffer(menu);
  setupMenu();
  display.display();
}
