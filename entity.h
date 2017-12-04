typedef struct Entity
{
	float x, y;
	byte width, height;
	Rect cbox; // used for cbox offset and size
	Rect collide; // used to actually calculate collisions

	float momY;
	float weight;
	float movementSpeed;
	float jumpStrength;

	byte frames;
	byte curFrame;
	int animationFrequency;

	void jump()
	{
		if (y + height == ground)
		{
			momY -= jumpStrength;
		}
	}

	void updateCollide()
	{
		collide = {.x = x + cbox.x, .y = y + cbox.y, .width = cbox.width, .height = cbox.height};
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
		if (arduboy.everyXFrames(animationFrequency))
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
