
#include "../inc/ft_malloc.h"
# define REPETITION 15
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
	char	*str1[REPETITION];
	char	*str[REPETITION];
	char	*str2[REPETITION];
	(void)ac;
	(void)(str);
	(void)(str1);
	(void)str2;
	i = atoi(av[2]);
	c = av[1][0];
	for (int j = 0; j < REPETITION ; j++)
	{
		write(1,"1",2);
		str1[j] = str_new_cpy(c, 1000);
		write(1,"2\n",2);
//		str[j] = str_new_cpy(c, i + 98);
		str2[j] = str_new_cpy(c, 5);
//		if (!(j %1000))
//			printf("%d\n",j);
	}
	for (int j = 0; j < REPETITION ; j++)
	{
	//	printf("str2 \t%lu\n", strlen(str2[j]));
	//	printf("str1 \t%lu\n", strlen(str1[j]));
//		printf("str \t%lu\n", strlen(str[j]));
	}
	show_alloc_mem();
	ft_free(str1[0]);
	ft_free(str[1]);
//	ft_free(str1[2]);
//	printf("malloc 1\n");
//	ft_malloc(102);
//	printf("malloc 2\n");
//	ft_malloc(105);
//	ft_malloc(110);
//	show_alloc_mem();
	return (0); // ou erreur
}
