
#include "../inc/ft_malloc.h"
# define REPETITION 6
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
	char	*str2[REPETITION];
	(void)ac;
	(void)(str);
	(void)(str1);
	(void)str2;
	i = atoi(av[2]);
	c = av[1][0];
	for (int j = 0; j < REPETITION ; j++)
	{
		printf("j = %d\n", j);
		write(1,"1",2);
//		str1[j] = str_new_cpy(c+j, 1000);
		write(1,"2\n",2);
//		ft_malloc(256);
//		ft_malloc(1024);
		str[j] = str_new_cpy('b', 1);
		str1[j] = str_new_cpy('a', 1023);
	//	str2[j] = str_new_cpy('a', 15000);
		dprintf(3,"str1 :%lu\n", strlen(str1[j]));
	//	dprintf(4,"str1 :%lu\n", strlen(str1[j]));
//		if (!(j %1000))
//			printf("%d\n",j);
	//	show_alloc_mem();
	}
	printf("\n\n\n");
	ft_free(str1[4]);
	ft_free(str1[3]);
	ft_free(str1[5]);
	ft_free(str1[1]);
	ft_free(str[1]);
	ft_free(str[2]);
	show_alloc_mem();
	exit (1);
	show_alloc_mem();
	exit (1);
	ft_free(str1[2]);
	exit (1);
	ft_free(str[5]);
	ft_free(str1[0]);
	str1[0] = str_new_cpy('a', 1023);
	str1[1] = str_new_cpy('a', 1023);
	str1[2] = str_new_cpy('a', 1023);
	str1[3] = str_new_cpy('a', 1023);
	str1[4] = str_new_cpy('a', 1023);
	str1[5] = str_new_cpy('a', 1023);
	show_alloc_mem();
//	ft_malloc(11);
	ft_realloc(str1[5], 11);
	//ft_free(str1[0]);
	//ft_free(str1[1]);
	//ft_free(str1[2]);
	//str_new_cpy('a', 1020);
	show_alloc_mem();
	return (0);
}

