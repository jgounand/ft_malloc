
#include "../inc/ft_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
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
	int fd2 = open("/dev/ttys002", O_RDWR);
	if (fd)
		;
	for (size_t j = 0; j < i ; j++)
	{
	    current_size = (j + 1 ) * 3;
		printf("j = %zu\n", j);
		write(1,"1",2);
		write(1,"2\n",2);
		val = rand() % 2056;
		str[j] = str_new_cpy('b', val);
	show_alloc_mem(fd2);
	show_table(str,j);
	dprintf(2,"check ptr after new alloc\n");
	check_ptr_prensent(str,j);
		dprintf(2,"check done\n");
		show_alloc_mem(2);
		 if (j > 3 && rand()% 20 < 5)
		{
			short tmp = rand() % (j);

			if (str[tmp] != NULL)
			{

				dprintf(fd," tmp %d %p\n",tmp, str[tmp]);
				str[tmp] = ft_realloc(str[tmp],rand() % 2056);
				dprintf(fd,"new realloc ptr %p\n",str[tmp]);
				show_alloc_mem(fd2);
				dprintf(2,"check ptr after realloc\n");
				check_ptr_prensent(str,j);
				dprintf(2,"check done\n");
				show_alloc_mem(2);
			}
		}
		if (j > 3 && rand()% 20 < 3)
		{
			short tmp = rand() % (j);
			if (str[tmp] != NULL)
			{
				ft_free(str[tmp]);
				str[tmp] = NULL;
				dprintf(2,"check ptr after free\n");
				check_ptr_prensent(str,j);
				dprintf(2,"check done\n");
				show_alloc_mem(2);
			}
		}
	}
	dprintf(2,"main 2\n");
	show_alloc_mem(1);
	test_05();
	return (0);
}


#define M (1024 * 1024)
void print(char *s)
{
	write(1, s, strlen(s));
}

int test_00()
 {
 	ft_malloc(25);
 	ft_malloc(1024);
 	ft_malloc(1024 * 32);
 	ft_malloc(1024 * 1024);
 	ft_malloc(1024 * 1024 * 16);
 	ft_malloc(1024 * 1024 * 128);
 	show_alloc_mem(1);
 	return 0;
 }

 int	test_01()
 {
 	char *addr;

 	addr = ft_malloc(16);
 	ft_free(NULL);
	 ft_free((void*)addr + 5);
 	if (ft_realloc((void*) + 5, 10) == NULL)
 	{
 		print("Bonjour\n");
 	}
 	return 0;
 }

 int	test_02()
 {
 	char *addr1;
 	char *addr2;
 	char *addr3;

 	addr1 = (char*)ft_malloc(16 * M);
 	strcpy(addr1, "Bonjour\n");
 	print(addr1);
 	addr2 = (char*)ft_malloc(16 * M);
 	addr3 = ft_realloc(addr1, 128 * M);
 	addr3[127 * M] = 42;
 	print(addr3);
 	return 0;
 }

int	test_03()
{
	int  i;
	char *addr;

	(void)addr;
	i = 0;
	while (i < 1024)
	{
		addr = (char*)ft_malloc(1024);
		if (addr == NULL)
		{
			ft_putstr("NULL returned!\n");
			return 0;
		}
		addr[0] = 42;
		ft_free(addr);
		i++;
	}
	show_alloc_mem(1);
	return 0;
}

 int	test_04()
 {
 	int  i;
 	char *addr;
 	char *tmp;

 	(void)addr;
 	i = 0;
 	while (i < 1024)
 	{
 		addr = (char*)ft_malloc(1024);
 		addr = ft_realloc(addr, 64);
 		if (addr == NULL)
 		{
 			ft_putstr("NULL returned!\n");
 			return 0;
 		}
 		addr[0] = 42;
		ft_free(addr);
 		i++;
 	}
 	addr = (char*)ft_malloc(1024);
 	strcpy(addr, "Bonjour\n");
 	tmp = (char*)ft_malloc(128);
 	addr = ft_realloc(addr, 64);
	 ft_free(tmp);
 	print(addr);
	 ft_free(addr);
	 ft_free(NULL);
 	if (ft_realloc(NULL, 0) == NULL)
 		print("Bonjour\n");
 	return 0;
 }

 int	test_05()
 {
 	ft_putstr("Malloc...\n");
 	ft_malloc(0);
 	ft_putstr("Free...\n");
	 ft_free(NULL);
 	ft_putstr("Realloc...\n");
 	ft_realloc(NULL, 0);
 	ft_putstr("Show alloc mem...\n");
 	show_alloc_mem(1);
 	printf("Page Size: %d", getpagesize());
 	return 0;
 }
