
#include "../inc/ft_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//ligne 1161395
char	*str_new_cpy(char c, size_t i)
{
	size_t	j;
	char	*str;

	j = 0;
	printf("--->size = %zu<---\n", i+ 1);
	str = ft_malloc(i + 1);
	dprintf(2, "add => %p\n",str);
	dprintf(2,"main 1\n");
	show_alloc_mem(2);
	dprintf(2,"--->fin alloc<---\n");
	show_alloc_mem(1);
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
	time_t t;
	char	c;
	size_t	i;
	i = atoi(av[2]);
	c = av[1][0];
	char	*str[i];
	char	*str1[i];
	char	*str2[i];
	int val = 0;
	(void)ac;
	(void)(str);
	(void)(str1);
	(void)str2;
	srand((unsigned) time(&t));
	for (size_t j = 0; j < i ; j++)
	{
	    current_size = j + 1;
		printf("j = %zu\n", j);
		write(1,"1",2);
//		str1[j] = str_new_cpy(c+j, 1000);
		write(1,"2\n",2);
//		ft_malloc(256);
		val = rand() % 2043;
        //dprintf(2,"j = %zu\n", j);
		str[j] = str_new_cpy('b', val);
		//dprintf(2,"j = %zu\n", j);
		//str1[j] = str_new_cpy('a', val);
	//	dprintf(2,"j = %zu\n", j);
		//str2[j] = str_new_cpy('c', val);
	//	str2[j] = str_new_cpy('a', 15000);
	//	dprintf(3,"str1 :%p\n", str1[j]);
	//	dprintf(3,"\t\tstr :%p\n", str1[j]);
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
	dprintf(2,"main 2\n");
	show_alloc_mem(1);
	return (0);
}

