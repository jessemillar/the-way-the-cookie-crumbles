typedef struct Entity
{
	float x = 10, y = 0;
	byte width = 16, height = 16;
	Rect cbox = {.x = x, .y = y, .width = width, .height = height};
	float momY = 0;
	float weight = 0.35;
	float jumpStrength = 5;
	byte frames = 6;
	byte curFrame = 0;
	int animationSpeed = 3;
	float movementSpeed = 1.5;

	void jump()
	{
		if (y + height == ground)
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
		if (y + height < ground)
		{
			momY += weight;
		}
		else
		{
			momY = 0;
			y = ground - height;
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

	void sketch(unsigned char sprite[])
	{
		sprites.drawPlusMask(int(x), int(y), sprite, curFrame);
	}
};
