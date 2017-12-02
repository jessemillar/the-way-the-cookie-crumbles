#include "images.h"

typedef struct Player
{
	byte floor = HEIGHT - 10;
	float x = 10, y = 0;
	byte width = 16, height = 16;
	float momY = 0;
	float weight = 0.35;
	float jumpStrength = 5;
	int maxScoreDigits = 7;
	byte frames = 6;
	byte curFrame = 0;
	int animationSpeed = 3;
	float movementSpeed = 1.5;
	int score = 0;

	void control()
	{
		if (arduboy.justPressed(A_BUTTON | B_BUTTON | UP_BUTTON))
		{
			jump();
		}

		if (arduboy.pressed(LEFT_BUTTON))
		{
			if (x - movementSpeed > 0)
			{
				animationSpeed = 4;
				x -= movementSpeed;
			}
		}
		else if (arduboy.pressed(RIGHT_BUTTON))
		{
			if (x + movementSpeed + width < WIDTH)
			{
				animationSpeed = 2;
				x += movementSpeed;
			}
		}
		else
		{
			animationSpeed = 3;
		}
	}

	void jump()
	{
		score++;

		if (y + height == floor)
		{
			momY -= jumpStrength;
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
		if (arduboy.everyXFrames(animationSpeed))
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
		String displayScore = String(score);

		while (displayScore.length() < maxScoreDigits)
		{
			displayScore = "0" + displayScore;
		}

		prettyPrintNumber(displayScore, WIDTH - maxScoreDigits * 7 - 3, 3);
	}

	void draw()
	{
		arduboy.fillRect(0, floor, WIDTH, HEIGHT - floor);
		sprites.drawSelfMasked(int(x), int(y), theodore, curFrame);
	}
} Player;
