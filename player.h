#include "images.h"

typedef struct Player
{
	byte floor = HEIGHT - 10;
	float x = 10, y = 0;
	byte width = 16, height = 16;
	byte momY = 0;
	float weight = 0.25;
	byte frames = 6;
	byte curFrame = 0;
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
		if (arduboy.everyXFrames(4))
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
