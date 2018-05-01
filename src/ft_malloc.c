/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/01 19:37:15 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

t_mem	*init_mem(void)
{

	if (g_mem)
		return (g_mem);
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * 3 + MAX_TINY + MAX_MED,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		write(2, "ERROR\n",6);
		return (NULL);
	}
	ft_bzero(g_mem, sizeof(t_mem) + MAX_TINY + MAX_MED + getpagesize() * 3);
	TINY_SIZE = MAX_HEADER(t_tny);
	MED_SIZE = MAX_HEADER(t_med);
	FAT_SIZE = MAX_HEADER(t_fat);
	g_mem->next = NULL;
	return (g_mem);
}

void *get_addr(void *ptr)
{
	while ((uintptr_t)ptr % 8)
		ptr++;
	printf("%lu %p\n", (size_t)&ptr % 8,ptr);
	return (ptr);
}

void	*add_small(short type, size_t lenght)
{
	t_tny *tmp;
	size_t	i;

	i = 0;
	tmp = type  == 0? H_TINY : H_MED;
	if (!g_mem->max_size[(int)type])
	{
		printf("il faut realouer !!\n");
		return (NULL);
	}
	while (tmp->size)
	{
		if (tmp->size < 0)
		{
			//checker si possible ajouter ici
			printf("ELEMENT FREEDC'est good\n");
			break;
		}
		tmp++;
	}
	if (tmp == H_TINY)
	{
		printf("tmp == H_TINY\n");
		tmp->ptr = get_addr((void *)g_mem + getpagesize()* 3);
		tmp->size = lenght;
	}
	else if (tmp == H_MED)
	{
		printf("tmp == H_MDE\n");
		tmp->ptr = get_addr((void *)g_mem + getpagesize()* 3 + MAX_TINY);
		tmp->size = lenght;
	}
	else
	{
		tmp->ptr = get_addr(1 + (tmp - 1)->ptr + (tmp - 1)->size);
		tmp->size = lenght;
	}
	if (!type)
		TINY_SIZE--;
	else
		MED_SIZE--;
	return (tmp->ptr);
}

void *ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	init_mem();
	if (size <= TINY)
		return (add_small(0, size));
	else if (size <= SMALL)
		return (add_small(1, size));
	else
		return (NULL);
	return (NULL);
}
