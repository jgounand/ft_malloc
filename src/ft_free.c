/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/07 18:16:09 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

short gettype(void *ptr)
{
	if (ptr < (void *)g_mem + getpagesize() * 3 + MAX_TINY)
	{
		printf("FREE TINY\n");
		return (0);
	}
	else if (ptr < (void *)g_mem + getpagesize() * 3 + MAX_TINY + MAX_MED)
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

static void	try_defragment(t_tny *tofree, size_t cpt)
{
	(void)cpt;
	printf("tofree + 1 %p\n",(tofree + 1)->ptr);
	if ((tofree + 1)->ptr)
	{
			printf("0\n");
		if ((tofree + 1)->size < 0)
		{
			tofree->size = -((uintptr_t)(tofree + 2)->ptr - (uintptr_t)tofree->ptr);
			printf("tofree->size %d\n", tofree->size);
			ft_memmove(tofree + 1, tofree + 2, (void *)H_TINY + MAX_HEADER(t_tny) - (void *)(tofree + 2));
			printf("tofree + 1)->ptr %p\n", (tofree + 1)->ptr);
			TINY_SIZE++;
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
				TINY_SIZE++;

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
				TINY_SIZE++;
			}
			else
			{
			printf("6\n");
			(tofree- 1)->size = -((uintptr_t)(tofree + 1)->ptr - (uintptr_t)(tofree - 1)->ptr);
			ft_memmove(tofree, tofree + 1, ((void *)H_TINY + MAX_HEADER(t_tny)) - (void *)(tofree + 1));
			printf("tofree->size %d\n", tofree->size);
				TINY_SIZE++;
			}
		}
	}
}

static void free_tny_small(t_tny *tofree, void *ptr)
{
	size_t	cpt;

	cpt = 0;
	while (tofree->ptr)
	{
		if (ptr == tofree->ptr)
		break;
		cpt++;
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
		try_defragment(tofree, cpt);
	}
}

static t_fat	*get_fat(void *ptr)
{
	t_fat	*tofree;

	tofree = (void *)g_mem + getpagesize() * 3;
	while (tofree->ptr)
	{
		if (ptr == tofree->ptr)
			return (tofree);
		tofree++;
	}
	//voir quand on realou une deuxieme fois
	return (NULL);
}


void ft_free(void *ptr)
{
	short	type;
	t_tny	*tofree_small;
	t_fat	*tofree_fat;

	tofree_small = NULL;
	tofree_fat = NULL;
	type = gettype(ptr);
	if (type <= 1)
		free_tny_small(!type ? H_TINY : H_MED, ptr);
	else
		tofree_fat = get_fat(ptr);
	if (tofree_small)
		printf("tofree %p %d\n", tofree_small->ptr, tofree_small->size);

}
