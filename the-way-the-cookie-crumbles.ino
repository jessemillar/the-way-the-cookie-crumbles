#include "globals.h"
#include "utils.h"
#include "compycore.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

Compycore compycore;
Player player;

const int enemyCount=5;
std::vector<Enemy> enemies;

void setup()
{
	arduboy.boot(); // raw hardware
	arduboy.blank(); // blank the display

	arduboy.flashlight(); // light the RGB LED and screen if UP button is being held.

	// check for and handle buttons held during start up for system control
	arduboy.systemButtons();

	arduboy.audio.begin();

	// wait for all buttons to be released
	do
	{
		arduboy.delayShort(50);
	}
	while (arduboy.buttonsState());

	arduboy.initRandomSeed();
}

void loop()
{
	if (!(arduboy.nextFrame())) return;

	arduboy.pollButtons();

	arduboy.clear();

	if (!(compycore.introduce())) return;

	// ground
	arduboy.fillRect(0, ground-3, WIDTH, HEIGHT-ground+3);

	// spawn a new enemy
	if (random(100)<2) {
		enemies.push_back(Enemy());
	}

	// do stuff with the enemies
	for(int i=0; i < enemies.size(); i++){
		if (enemies[i].x>(0-enemies[i].width)) {
			enemies[i].update();
			enemies[i].draw();
		} else {
			enemies.erase(enemies.begin() + i);
			i--;
		}
	}

	Serial.print("Collision");

	player.update();
	player.drawScore();
	player.draw();

	arduboy.display();
}
