#include <stdio.h>

int main(int ac, char **av)
{
	if (ac == 1)
		return 0;
	for (int i = 1; av[i]; i++)
		printf("%d %s\n", i, av[i]);
	return 0;
}
