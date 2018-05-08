/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/08 17:55:56 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

short gettype(void *ptr)
{
	t_start	*start;

	start = (t_start *)(g_mem + 1);
	printf("ptr %p tiny %p\n", ptr, (void *)start->start + MAX_TINY);
	if (ptr < ((void *)start->start + MAX_TINY))
	{
		printf("FREE TINY\n");
		return (0);
	}
	else if (ptr < (void *)start->start + MAX_TINY + MAX_MED)
	{
		printf("FREE MED\n");
		return (1);
	}
	else
	{
		printf("FREE FAT\n");
		return (2);
	}
}

static void	try_defragment(t_tny *tofree)
{
	short	type;

	type = gettype(tofree->ptr);
	printf("tofree + 1 %p\n",(tofree + 1)->ptr);
	if ((tofree + 1)->ptr)
	{
			printf("0\n");
		if ((tofree + 1)->size < 0)
		{
			tofree->size = -((uintptr_t)(tofree + 2)->ptr - (uintptr_t)tofree->ptr);
			printf("tofree->size %d\n", tofree->size);
			ft_memmove(tofree + 1, tofree + 2, (void *)(type ? H_MED :H_TINY) + MAX_HEADER(t_tny) - (void *)(tofree + 2));
			printf("tofree + 1)->ptr %p\n", (tofree + 1)->ptr);
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
			printf("1\n");
		}
		else
		{
			printf("2\n");
			tofree->size = -((uintptr_t)(tofree + 1)->ptr - (uintptr_t)tofree->ptr);
			printf("tofree->size %d\n", tofree->size);
		}
	}
	else
	{
			printf("3\n");
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;

		ft_bzero(tofree, sizeof(t_tny));
	}

	if (tofree != H_TINY && tofree != H_MED && (tofree - 1)->ptr)
	{
		if ((tofree -1)->size < 0)
		{
			printf("4\n");
			if (!tofree->size)
			{
			printf("5\n");
			ft_bzero(tofree - 1, sizeof(t_tny));
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
			}
			else
			{
			printf("6\n");
			(tofree- 1)->size = -((uintptr_t)(tofree + 1)->ptr - (uintptr_t)(tofree - 1)->ptr);
			ft_memmove(tofree, tofree + 1, ((void *)(type ? H_MED : H_TINY) + MAX_HEADER(t_tny)) - (void *)(tofree + 1));
			printf("tofree->size %d\n", tofree->size);
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
			}
		}
	}
}

static void free_tny_small(t_tny *tofree, void *ptr)
{
	while (tofree->ptr)
	{
		if (ptr == tofree->ptr)
		break;
		tofree++;
	}
	//voir quand on realou une deuxieme fois
	if (!tofree)
	{
		printf("error tmp null\n");
		exit(2);
	}
	else
	{
		try_defragment(tofree);
	}
}

static int	free_fat(void *ptr)
{
	t_fat	*tofree;

	printf("FREE FAT\n");
	tofree = H_FAT;
	while (tofree->ptr)
	{
		if (ptr == tofree->ptr)
			break;
		tofree++;
	}
	if ((tofree + 1)->size)
	{
		ft_memmove(tofree, tofree + 1, (void *)H_FAT + MAX_HEADER(t_fat) - (void *)(tofree + 1));
	}
	FAT_SIZE++;
	//voir quand on realou une deuxieme fois
	return (0);
}

void ft_free(void *ptr)
{
	short	type;

	type = 99;
	printf("type %d ptr %p\n", type, ptr);
	type = gettype(ptr);
	if (type <= 1)
		free_tny_small(!type ? H_TINY : H_MED, ptr);
	else
		free_fat(ptr);
}
