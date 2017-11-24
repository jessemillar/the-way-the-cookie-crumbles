#include <Arduboy2.h>
#include <Sprites.h>

#include "images.h"

Arduboy2 arduboy;
Sprites sprites;

typedef struct Player
{
	uint8_t floor = 40;
	uint8_t x = 10, y = 30;
	uint8_t momY = 0;
	uint8_t frames = 6;
	uint8_t curFrame = 0;
	int score = 0;

	void jump()
	{
		momY += 5;
	}

	void physics()
	{
		gravity();
	}

	void gravity()
	{
		if (y < floor)
		{
			y++;
		}
		else
		{
			y = floor;
		}
	}

	void animate()
	{
		if (arduboy.everyXFrames(3))
		{
			if (curFrame < frames - 1)
			{
				curFrame += 1;
			}
			else
			{
				curFrame = 0;
			}
		}
	}

	void drawScore()
	{
		arduboy.setCursor(2, 2);
		arduboy.print(score);
	}

	void draw()
	{
		sprites.drawSelfMasked(x, y, theodore, curFrame);
	}
} Player;
