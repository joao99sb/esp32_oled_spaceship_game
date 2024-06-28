#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <vector>

#include "../include/matrix.h"
#include "../include/menu.h"
#include "../include/spaceship.h"
#include "../include/buffer.h"
#include "../include/staticEntity.h"
#include "../include/enemies.h"
#include "../include/sound.h"

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
int score = 0;
int lives = 3;
void setupMenu()
{

  StaticEntity *menu_text = new StaticEntity(MENU_HEIGHT, SCREEN_WIDTH, 0, 0);
  menu_text->populateMatrix(0);

  for (int i = 0; i < SCREEN_WIDTH; i++)
  {
    menu_text->setMatrixValue(MENU_HEIGHT - 1, i, 1);
  }
  menu->drawImageFromMatrix(menu_text, 0, 0);
  display.setTextSize(1);      // Tamanho do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0, 0);     // Posição inicial do texto (x, y)

  // Exibe "Hello, world!" na tela
  display.display();
}

void showSideBar()
{
  display.setTextSize(1);      // Tamanho do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0, 0);     // Posição inicial do texto (x, y)

  display.printf("score: %d    vidas: %d", score, lives);
}

void loseGameMsg()
{
  display.clearDisplay();
  display.setTextSize(1);      // Tamanho do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0, 0);     // Posição inicial do texto (x, y)

  // Exibe "Hello, world!" na tela
  display.println("voce perdeu");
  display.setTextSize(2);
  display.printf("\nscore: %d", score);
  display.display();
}

void initializeGameMsg()
{
  display.clearDisplay();
  display.setTextSize(2);      // Tamanho do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(0, 0);     // Posição inicial do texto (x, y)

  // Exibe "Hello, world!" na tela
  display.println("Pressione algum botao para comecar");
  display.display();
}

std::vector<Enemies *> enemies_list;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Não faça nada se falhar
  }
  setupSound();
  // button setup
  pinMode(BUTTON_PIN_1, INPUT);
  pinMode(BUTTON_PIN_2, INPUT);
  pinMode(BUTTON_PIN_3, INPUT);

  display.clearDisplay(); // Limpa o buffer do display

  gameBuffer = new Buffer(SCREEN_HEIGHT, SCREEN_WIDTH);
  gameBuffer->populateMatrix(0);
  menu = new Buffer(MENU_HEIGHT, SCREEN_WIDTH);
  setupMenu();

  spaceship = new Spaceship(SPACE_HEIGHT, SPACE_WIDTH,
                            spaceship_y_pos, spaceship_x_pos,
                            spaceship_max_y_pos, SCREEN_WIDTH,
                            1, 1);
  laser.blok = new StaticEntity(1, 10, spaceship_y_pos, 20);
  laser.blok->populateMatrix(1);
  laser.is_laser_able = true;
  laser.laser_timer = 5;

  initializeGameMsg();
  while (digitalRead(BUTTON_PIN_1) == LOW &&
         digitalRead(BUTTON_PIN_2) == LOW &&
         digitalRead(BUTTON_PIN_3) == LOW)
  {
    ;
  }
  playInitialSound();
}
void remove_enemie(int index)
{

  delete enemies_list[index];                       // Libera a memória do objeto
  enemies_list.erase(enemies_list.begin() + index); // Remove o ponteiro do vetor
}
void check_collision_with_enemies()
{
  for (int i = 0; i < enemies_list.size(); i++)
  {
    Enemies *enemy = enemies_list[i];

    int laserY = laser.blok->getCurrentY();
    int enemyY = enemy->getCurrentY();
    int laserWidth = laser.blok->getWidth();
    int laserHeight = laser.blok->getHeight();
    int enemyWidth = enemy->getWidth();
    int enemyHeight = enemy->getHeight();

    // Verifica se há interseção entre o laser e o inimigo

    if (
        (laserY + MENU_HEIGHT >= enemyY) &&
        (laserY <= enemyY + enemyHeight - MENU_HEIGHT))
    {

      remove_enemie(i);
      score++;
      break;
    }
  }
}

void handle_actions()
{
  int up_btn_state = digitalRead(BUTTON_PIN_1);
  int down_btn_state = digitalRead(BUTTON_PIN_2);
  int laser_btn_state = digitalRead(BUTTON_PIN_3);

  if (up_btn_state == HIGH)
  {
    spaceship->moveUp();
    spaceship->increaseSpeed();
    spaceship->increaseSpeed();
  }
  if (down_btn_state == HIGH)
  {
    spaceship->moveDown();
    spaceship->increaseSpeed();
    spaceship->increaseSpeed();
  }

  if (up_btn_state == LOW && down_btn_state == LOW)
  {
    spaceship->setSpeed(3);
  }

  if (laser_btn_state == HIGH && laser.is_laser_able)
  {

    laser.blok->setCurrentX(SCREEN_WIDTH / 5);

    int spaceship_center_position = spaceship->getCurrentY() + spaceship->getHeight() / 2;
    laser.blok->setCurrentY(spaceship_center_position); // Começa do centro do foguete
    gameBuffer->drawImageFromMatrix(laser.blok, laser.blok->getCurrentY() + GAME_BUFFER_START, 20);

    playLaserSound();
    laser.is_laser_able = false;

    check_collision_with_enemies();
  }

  if (!laser.is_laser_able)
  {
    laser.laser_timer--;
    if (laser.laser_timer == 0)
    {
      laser.is_laser_able = true;
      laser.laser_timer = 5;
    }
  }
}

int enemies_clock = 25;

void enemies_move(Enemies *enemies, int index)
{
  enemies->moveLeft();
  if (enemies->getCurrentX() == 0)
  {
    enemies->setCurrentX(0);
    lives--;
    remove_enemie(index);
  }
}

static float difculty_level_step = 0.1;
int enemies_speed = 2;
void handle_enimies()
{

  difculty_level_step += 0.1;

  if ((int)difculty_level_step % 20 == 0 && (int)difculty_level_step != 0)
  {
    enemies_speed++;
    difculty_level_step += 1;
  }
  if (enemies_clock == 0)
  {

    for (int i = 0; i < enemies_speed - 1; i++)
    {

      int random_y_position = random(GAME_BUFFER_START, SCREEN_HEIGHT - 10);
      Enemies *new_enemie = new Enemies(10, 7, random_y_position, SCREEN_WIDTH, enemies_speed, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
      enemies_list.push_back(new_enemie);
    }

    // int factor = enemies_speed - 2;

    // enemies_clock = 30 - factor;

    enemies_clock = 25;
  }
  else
  {
    enemies_clock--;
  }
}

void endGame()
{
  playGameOverSound();
  int up_btn_state = digitalRead(BUTTON_PIN_1);
  int down_btn_state = digitalRead(BUTTON_PIN_2);
  int laser_btn_state = digitalRead(BUTTON_PIN_3);
  loseGameMsg();
  if (enemies_list.size() > 0)
  {
    for (int i = 0; i < enemies_list.size(); i++)
    {
      remove_enemie(i);
    }
  }

  while (up_btn_state == LOW && down_btn_state == LOW && laser_btn_state == LOW)
  {
    up_btn_state = digitalRead(BUTTON_PIN_1);
    down_btn_state = digitalRead(BUTTON_PIN_2);
    laser_btn_state = digitalRead(BUTTON_PIN_3);
  }
  score = 0;
  enemies_speed = 2;
  difculty_level_step = 0.1;
  lives = 3;
}

void loop()
{

  if (lives <= 0)
  {
    endGame();
    delay(500);
  }
  gameBuffer->resetBuffer();

  // draw menu
  // drawImageFromMatrix(menu, 0, 0);
  handle_actions();

  handle_enimies();
  for (int i = 0; i < enemies_list.size(); i++)
  {
    enemies_move(enemies_list[i], i);

    gameBuffer->drawImageFromMatrix(enemies_list[i], enemies_list[i]->getCurrentY(), enemies_list[i]->getCurrentX());
  }

  // draw image
  gameBuffer->drawImageFromMatrix(spaceship, spaceship->getCurrentY() + MENU_HEIGHT, 0);
  display.clearDisplay();
  updateDisplayFromBuffer(gameBuffer);
  updateDisplayFromBuffer(menu);
  showSideBar();
  display.display();
}
