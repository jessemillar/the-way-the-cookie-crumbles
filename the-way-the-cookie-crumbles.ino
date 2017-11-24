#include <Arduboy2.h>

#include "player.h"

Player player;

void setup()
{
	arduboy.begin();
}

void loop()
{
	if (!(arduboy.nextFrame())) return;

	arduboy.pollButtons();

	arduboy.clear();

	player.animate();
	player.physics();
	player.drawScore();
	player.draw();

	arduboy.display();
}