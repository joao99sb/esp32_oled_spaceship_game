#include "../include/sound.h"
#include <Arduino.h>

void setupSound()
{
  ledcSetup(0, 2000, 8); // Configura o canal 0 com frequência de 2kHz e resolução de 8 bits
  // Anexa o pino do buzzer ao canal PWM especificado
  ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
}

void playLaserSound()
{
  // Frequência e duração para o som do laser disparando
  const int LASER_FREQUENCY = 5000; // 1000 Hz
  const int LASER_DURATION = 90;    // 200 ms

  ledcWriteTone(BUZZER_CHANNEL, LASER_FREQUENCY);
  delay(LASER_DURATION / 3);
  ledcWriteTone(BUZZER_CHANNEL, LASER_FREQUENCY / 3); // Para o som
  delay(LASER_DURATION / 3);
  ledcWriteTone(BUZZER_CHANNEL, LASER_FREQUENCY / 3); // Para o som

  delay(LASER_DURATION / 3); // Para o som
  ledcWriteTone(BUZZER_CHANNEL, 0);
}

void playGameOverSound()
{
  int gameOverMelody[] = {349, 392, 440, 494, 523};
  int noteDurations[] = {125, 125, 125, 125, 125};
  for (int i = 0; i < sizeof(gameOverMelody) / sizeof(int); i++)
  {
    ledcWriteTone(0, gameOverMelody[i]); // Toca a nota
    delay(noteDurations[i]);             // Espera pela duração da nota
    ledcWriteTone(0, 0);                 // Para o som
    delay(50);                           // Pequena pausa entre as notas
  }
}

void playInitialSound()
{
  int startGameMelody[] = {
      NOTE_C4,
      NOTE_D4,
      NOTE_F4,
      NOTE_G4,
      NOTE_A4,
      NOTE_B3,
      NOTE_C4,
      NOTE_D4,
      NOTE_E4,
      NOTE_F4,
      NOTE_G4,
      NOTE_A4,
  };
  // Durações das notas (em milissegundos)
  // int noteDurations[] = {125, 125, 125, 125, 125, 125};

  for (int i = 0; i < sizeof(startGameMelody) / sizeof(int); i++)
  {
    ledcWriteTone(0, startGameMelody[i]); // Toca a nota
    delay(125);                           // Espera pela duração da nota
    ledcWriteTone(0, 0);                  // Para o som
    delay(50);                            // Pequena pausa entre as notas
  }
}