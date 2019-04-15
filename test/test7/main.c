
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include "../inc/ft_malloc.h"
int test_00();
int test_01();
int test_02();
int test_03();
int test_04();
int test_05();

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

void show_table(char *tab[], size_t size)
{
	size_t i = 0;
	int fd = open("/dev/ttys002", O_RDWR);
	while (i <= size)
	{
		dprintf(fd,"i : %lu %p \n",i , tab[i]);
		i++;
	}
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
	if (val)

	(void)ac;
	(void)(str);
	(void)(str1);
	(void)str2;
	srand((unsigned) time(&t));
	int fd = open("/dev/ttys001", O_RDWR);
	if (fd)
		;
	size_t total = 0;
	for (size_t j = 0; j < i ; j++)
	{
		val = rand() % 4064;
		str[j] = str_new_cpy('b', val);
		total += val;
		 if (j > 3 && rand()% 20 < 5)
		{
			short tmp = rand() % (j);

			if (str[tmp] != NULL)
			{
				str[tmp] = realloc(str[tmp],rand() % 2056);
			}
		}
		if (j > 3 && rand()% 20 < 3)
		{
			short tmp = rand() % (j);
			if (str[tmp] != NULL)
			{
				free(str[tmp]);
				str[tmp] = NULL;
			}
		}
	}
	return (0);
}


#define M (1024 * 1024)
void print(char *s)
{
	write(1, s, strlen(s));
}
