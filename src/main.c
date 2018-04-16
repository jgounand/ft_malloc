
#include "../inc/ft_malloc.h"

int	main(int ac, char **av)
{
	char	c;
	size_t	i;
	char	*str;

	i = atoi(av[1]);
	c = av[2][0];
	str = ft_malloc(i + 1);
	str[i] = '\0';
	while (--i)
	{
		str[i] = c;
	}
	return (0); // ou erreur
}
