#pragma once
#include "./pitches.h"
#define BUZZER_PIN 23

const int BUZZER_CHANNEL = 0;

void setupSound();
void playLaserSound();
void playGameOverSound();
void playInitialSound();