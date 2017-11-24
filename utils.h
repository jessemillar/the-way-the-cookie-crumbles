int countDigits(int number)
{
	int length = 1;

	while (number /= 10)
	{
		length++;
	}

	return length;
}
