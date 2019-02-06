
#include "../inc/ft_malloc.h"
char	*str_new_cpy(char c, size_t i)
{
	size_t	j;
	char	*str;

	j = 0;
	str = ft_malloc(i + 1);
	dprintf(2, "add => %p\n",str);
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
	i = atoi(av[2]);
	c = av[1][0];
	char	*str[i];
	char	*str1[i];
	char	*str2[i];
	(void)ac;
	(void)(str);
	(void)(str1);
	(void)str2;
	for (size_t j = 0; j < i ; j++)
	{
		printf("j = %zu\n", j);
		write(1,"1",2);
//		str1[j] = str_new_cpy(c+j, 1000);
		write(1,"2\n",2);
//		ft_malloc(256);
//		ft_malloc(1024);
		str[j] = str_new_cpy('b', 1);
		str1[j] = str_new_cpy('a', 254);
	//	str2[j] = str_new_cpy('c', 2055);
	//	str2[j] = str_new_cpy('a', 15000);
		dprintf(3,"str1 :%p\n", str1[j]);
		dprintf(3,"\t\tstr :%p\n", str1[j]);
//		if (!(j %1000))
//			printf("%d\n",j);
	//	show_alloc_mem();
	}
	/**
	printf("ok pour le moment \n");
	printf("\n\n\n");
	ft_free(str1[4]);
	ft_free(str1[3]);
	show_alloc_mem();
	ft_free(str1[5]);
	ft_free(str[1]);
	ft_free(str[2]);
	ft_free(str1[1]);
	ft_free(str1[2]); //bug quand je supprime un header
	ft_free(str[5]);
	ft_free(str1[0]);
	show_alloc_mem();
	str1[0] = str_new_cpy('a', 1023);
	str1[1] = str_new_cpy('a', 1023);
	str1[2] = str_new_cpy('a', 1023);
	str1[3] = str_new_cpy('a', 1023);
	str1[4] = str_new_cpy('a', 1023);
	str1[5] = str_new_cpy('a', 1023);
//	ft_malloc(11);
	how_alloc_mem();
	ft_realloc(str1[5], 11);
	ft_realloc(str2[5], 12);
	ft_free(str1[0]);
	ft_free(str2[0]);
	ft_free(str2[1]);
	ft_free(str2[2]);
	ft_free(str2[3]);
	ft_free(str2[4]);
	ft_free(str1[1]);
	ft_free(str1[2]);
	str_new_cpy('a', 1000);
	 **/
	show_alloc_mem();
	return (0);
}

