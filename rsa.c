#include <stdio.h>
#include <stdlib.h>

void factors(int num)
{
	int i;

	for (i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
		{
			printf("%d=%d*%d\n", num , i , num / i);
		}
	}
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: factors <file>\n");
		return (1);
	}

	char *filen = argv[1];
	FILE *file = fopen(filen, "r");
	if (file == NULL)
	{
		printf("Error opening file.\n");
		return (1);
	}

	int num;
	while (fscanf(file, "%d\n", &num) != EOF)
	{
		factors(num);
	}

	fclose(file);
	return (0);
}
