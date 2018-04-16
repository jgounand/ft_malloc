
#include "../inc/ft_malloc.h"


char	*str_new_cpy(char c, size_t i)
{
	size_t	j;
	char	*str;

	j = 0;
	str = ft_malloc(i + 1);
	while (j < i)
	{
		str[j] = c;
		j++;
	}
	str[j] = '\0';
	return (str);
}



int	main(int ac, char **av)
{
	char	c;
	size_t	i;
	char	*str;

	(void)ac;
	i = atoi(av[2]);
	c = av[1][0];
//	str = malloc(i + 1);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	str = str_new_cpy(c, i);
	ft_putendl(str);
	return (0); // ou erreur
}
