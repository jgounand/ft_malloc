/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/09 18:44:26 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;
/*
t_mem	*init_mem(void)
{

	if (g_mem)
		return (g_mem);
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * 4 + MAX_TINY + MAX_MED,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		write(2, "ERROR\n",6);
		return (NULL);
	}
	ft_bzero(g_mem, sizeof(t_mem) + MAX_TINY + MAX_MED + getpagesize() * 4);
	TINY_SIZE = MAX_HEADER(t_tny);
	MED_SIZE = MAX_HEADER(t_med);
	FAT_SIZE = MAX_HEADER(t_fat);
	return (g_mem);
}
*/
void *get_addr(void *ptr)
{
	while ((uintptr_t)ptr % 8)
		ptr++;
	printf("%lu %p\n", (size_t)&ptr % 8,ptr);
	return (ptr);
}

void	*add_node_free(t_tny *tmp, void *ptr, bool type)
{
		ft_memmove(tmp + 2, tmp + 1,(void *)(type ? H_MED : H_TINY) + MAX_HEADER(t_tny, 0 + (type ? S_HEADER_M : S_HEADER_T)) - (void *)(tmp + 1));
	(tmp + 1)->ptr = ptr;
	(tmp + 1)->size = -((uintptr_t)(tmp + 2)->ptr - (uintptr_t)(tmp + 1)->ptr);
	printf("add_node_free\n");
return (NULL);
}

void	*add_small(short type, size_t lenght)
{
	t_tny *tmp;
	t_start	*start;
	short	split_node_free;

	split_node_free = 0;
	//tmp = type == 1? H_MED : H_TINY;
	if (!g_mem->max_size[(int)type])
	{
		printf("il faut realouer !!\n");
		add_mem_header(type);
	}
	if (type == 1)
		tmp = H_MED;
	else
		tmp = H_TINY;
	

	printf("type %d %p\n", type, tmp);

	start = (t_start *)(g_mem + 1);
		printf("start->start %p", start->start);
	while (tmp->size)
	{
		if (tmp->size < 0 && lenght <= (size_t)-tmp->size)
		{
			split_node_free = 2;
				printf("10 lenght %lu => %lu type %d %d\n",lenght ,((tmp + 1)->ptr - get_addr(tmp->ptr + lenght + 1)), type, (type ? TINY + 1 : 1)) ;
			if  (((tmp + 1)->ptr - get_addr(tmp->ptr + lenght + 1)) > (1 + type ? 0 : TINY))
			{
				printf("10.1\n");
				split_node_free = 1;
			}
			break;
		}
		tmp++;
//		printf("+");
	}
		printf("\n");
		printf("tmp %p tmp - 1 %p\n", tmp, tmp -1);
	if (split_node_free == 1)
	{
		printf("tmp->ptr %p , new (tmp +1)->ptr %p , tmp + 1->ptr %p", tmp->ptr, get_addr(tmp->ptr + lenght + 1), (tmp+1)->ptr);
add_node_free(tmp, get_addr(tmp->ptr + lenght + 1), type);
	}
	if (tmp == H_TINY)
	{
				printf("11\n");
		printf("tmp == H_TINY size %lu\n", lenght);
//retroruver addresse du ptr;
		tmp->ptr = get_addr(start->start);
		tmp->size = lenght;
		printf("ptr %p\n", tmp->ptr);
	}
	else if (tmp == H_MED)
	{
				printf("=>12 lenght %lu\n", lenght);
		printf("tmp == H_MDE\n");
		tmp->ptr = get_addr(start->start+ MAX_TINY);
		tmp->size = lenght;
		printf("ptr %p\n", tmp->ptr);
	}
	else
	{
		printf("tmp -1 ptr %p\n", (tmp-1)->ptr);
//		if (get_addr((tmp - 1)->ptr + (tmp - 1)->size) + lenght > start->start + MAX_TINY + MAX_MED)
//		{
//			printf("je dous realouer !!\n");
//			exit (1);
//		}
		// checker si ce n est pas trop grand
				printf("13 prt -1 %p\n", (tmp-1)->ptr);
		tmp->ptr = get_data(get_addr((tmp - 1)->ptr + (tmp - 1)->size + 1),type, lenght);
		tmp->size = lenght;
		printf("ptr %p\n", tmp->ptr);
	}
	if (split_node_free != 2)
	{
		printf("add 1\n");
	if (!type)
		TINY_SIZE--;
	else
		MED_SIZE--;
	}return (tmp->ptr);
}

void	*add_fat(size_t lenght)
{
	t_fat *tmp;

	printf("ADD FAT\n");
	//tmp = type == 1? H_MED : H_TINY;
	if (!g_mem->max_size[2])
	{
		printf("il faut realouer !!\n");
		add_mem_header(2);
	}
	tmp = H_FAT; 
	printf("type %p tmp->size %lu \n", tmp, tmp->size);
	while (tmp->size)
	{
		printf("+");
		tmp++;
	}
		printf("-\n");
	printf("tmp == H_FAT size %lu\n", lenght);
//retroruver addresse du ptr;
	tmp->ptr = mmap(NULL,lenght, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	tmp->size = lenght;
		printf("ptr %p\n", tmp->ptr);
	FAT_SIZE--;
	return (tmp->ptr);
}

void *ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	init_mem();
	if (size <= TINY)
		return (add_small(0,size));
	else if (size <= SMALL)
		return (add_small(1,size));
	else
		return (add_fat(size));
	return (NULL);
}
