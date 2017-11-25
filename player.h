#include <Arduboy2.h>
#include <Sprites.h>

#include "images.h"

Arduboy2 arduboy;
Sprites sprites;

typedef struct Player
{
	uint8_t floor = HEIGHT - 10;
	uint8_t x = 10, y = 0;
	uint8_t width = 16, height = 16;
	uint8_t momY = 0;
	uint8_t weight = 1;
	uint8_t frames = 6;
	uint8_t curFrame = 0;
	int score = 0;

	void control()
	{
		if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON))
		{
			jump();
		}
	}

	void jump()
	{
		if (y + height == floor)
		{
			momY -= 8;
		}
	}

	void physics()
	{
		y += momY;

		gravity();
	}

	void gravity()
	{
		if (y + height < floor)
		{
			momY += weight;
		}
		else
		{
			momY = 0;
			y = floor - height;
		}
	}

	void animate()
	{
		if (arduboy.everyXFrames(2))
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
		arduboy.fillRect(0, floor, WIDTH, HEIGHT - floor);
		sprites.drawSelfMasked(x, y, theodore, curFrame);
	}
} Player;
