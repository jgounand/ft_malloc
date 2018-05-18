
#include "../inc/ft_malloc.h"
# define REPETITION 130560
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
//	(void)(str);
//	(void)(str1);
//	(void)str2;
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
	//	dprintf(5,"%s\n",str_new_cpy('b', 1));
		str[j] = str_new_cpy('a', 1023);
		str1[j] = str_new_cpy('a', 1);
		dprintf(3,"str :%lu\n", strlen(str[j]));
		dprintf(4,"str1 :%lu\n", strlen(str1[j]));
//		if (!(j %1000))
//			printf("%d\n",j);
	//	show_alloc_mem();
	}
	show_alloc_mem();
	for (int j = 0; j < REPETITION ; j++)
	{
		dprintf(3,"str :%p\n", str[j]);
		dprintf(4,"str1 :%p\n", str1[j]);
	}
//	show_alloc_mem();
	//	printf("str1 \t%lu\n", strlen(str1[j]));
	//	printf("str \t%lu\n", strlen(str[j]));
//	ft_free(str2[2]);
//	ft_free(str2[1]);
//	ft_free(str[3]);
	//ft_free(NULL);
//	char	*a = ft_malloc(2500);
//	ft_free(a);
//	ft_free(str1[0]);
//	ft_free(str2[3]);
//	ft_free(str2[2]);
//ft_free(str2[3]);
//:w
//ft_malloc(7);
//	ft_free(str1[3]);
//	ft_free(str1[2]);
//	printf("malloc 1\n");
//	show_alloc_mem();
//	ft_malloc(10);
//	ft_malloc(7);
//	ft_malloc(1010);
//	ft_malloc(800);
//	ft_malloc(500);
//	ft_malloc(1000);
//	ft_malloc(1000);
//	ft_malloc(700);
//	ft_malloc(4);
	
	//ft_free(tmp);
//	printf("malloc 2\n");
//	ft_malloc(105);
//	ft_malloc(110);
//	show_alloc_mem();
	return (0); // ou erreur
}

