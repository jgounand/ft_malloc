
#include "../inc/ft_malloc.h"

int	main(int ac, char **av)
{
	char	c;
	size_t	i;
	char	*str;
	size_t	j;

	(void)ac;
	i = atoi(av[2]);
	c = av[1][0];
	str = malloc(i + 1);
//	str = ft_malloc(i + 1);
	printf("i %lu str %p\n", i, str);
	j = 0;
	while (j < i)
	{
		str[j] = c;
		j++;
	}
	str[j] = '\0';
	ft_putendl(str);
	return (0); // ou erreur
}
