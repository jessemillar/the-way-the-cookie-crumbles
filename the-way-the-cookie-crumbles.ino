#include "globals.h"
#include "utils.h"
#include "compycore.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

Compycore compycore;
Player player;
Enemy enemy;

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
}

void loop()
{
	if (!(arduboy.nextFrame())) return;

	arduboy.pollButtons();

	arduboy.clear();

	if (!(compycore.introduce())) return;

	// ground
	arduboy.fillRect(0, ground, WIDTH, HEIGHT - ground);

	enemy.update();
	enemy.draw();

	player.update();
	player.drawScore();
	player.draw();

	arduboy.display();
}
