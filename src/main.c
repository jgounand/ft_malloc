
#include "../inc/ft_malloc.h"

# define REPETITION 5
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
	char	*str[REPETITION];
	char	*str1[REPETITION];

	(void)ac;
	i = atoi(av[2]);
	c = av[1][0];
	for (int j = 0; j < REPETITION ; j++)
	{
		write(1,"2",2);
		str1[j] = str_new_cpy(c, i);
		write(1,"1\n",2);
		//str[j] = str_new_cpy(c, i + 100);
	}
	for (int j = 0; j < REPETITION ; j++)
	{
		printf("j\tstr  %s\n\tst1r %s\n", str[j], str1[j]);
	}
	printf("id %d\n", ((t_key*)(g_mem + 1))->key);
	return (0); // ou erreur
}
