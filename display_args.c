#include <stdio.h>

int main(int ac, char **av)
{
	if (ac == 1)
		return 0;
	for (int i = 0; av[i]; i++)
		printf("%s\n", av[i]);
	return 0;
}
