/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/17 17:30:21 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
   short gettype(void *ptr)
   {
   t_start	*start;

   start = (t_start *)(g_mem + 1);
   printf("ptr %p\n", ptr);
   if (ptr < ((void *)start->start + MAX_TINY) && ptr >= start->start)
   {
   printf("FREE TINY\n");
   return (0);
   }
   else if (ptr < (void *)start->start + MAX_TINY + MAX_MED && ptr >= start->start+ MAX_MED)
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
   */

short	get_type(void *ptr)
{
	t_start	*start;

	if (!get_start(ptr, 1))
	{
		printf("Eror %p doesn't exist\n", ptr);
		exit (4);
	}
	start = get_start(ptr, 0);
	if (ptr < start->start + MAX_TINY && ptr >= start->start)
		return (0);
	else if (ptr < start->start + MAX_TINY + MAX_MED && ptr >= start->start + MAX_TINY)
		return (1);
	else if (0)
	{
		//check fat
		return (2);
	}
	else
	{
		printf("Error free %p doesn't exist\n", ptr);
		exit (4);
	}
}


static bool	not_begin_data(t_tny *tofree)
{
	void	*ptr;

	ptr = get_start(tofree->ptr, 0);
	if (ptr == tofree->ptr || (ptr + MAX_TINY) == tofree->ptr)
		return (0);
	return (1);
}

static void	try_defragment(t_tny *tofree)
{
	short	type;

	type = get_type(tofree->ptr);
	printf("tofree + 1 %p\n",(tofree + 1)->ptr);
	printf("0\n");
	if ((tofree + 1)->size < 0)
	{
		show_alloc_mem();
		tofree->size = -((uintptr_t)(tofree + 2)->ptr - (uintptr_t)tofree->ptr);
		printf("tofree->size %d\n", tofree->size);
		ft_memmove(tofree + 1, tofree + 2, (void *)(type ? H_MED :H_TINY) + MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)) - (void *)(tofree + 2));
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

	if (not_begin_data(tofree))
	{
		if ((tofree -1)->size < 0)
		{
			printf("6\n");
			(tofree- 1)->size = -((uintptr_t)(tofree + 1)->ptr - (uintptr_t)(tofree - 1)->ptr);
			ft_memmove(tofree, tofree + 1, ((void *)(type ? H_MED : H_TINY) + MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T))) - (void *)(tofree + 1));
			printf("tofree->size %d\n", tofree->size);
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
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
		try_defragment(tofree);
}

static int	free_fat(void *ptr)
{
	t_fat	*tofree;

	printf("FREE FAT ptr => %p\n", ptr);
	tofree = H_FAT;
	while (tofree->ptr)
	{
		if (ptr == tofree->ptr)
			break;
		tofree++;
	}
	if (!tofree->ptr)
	{
		//error
	}
	else
		munmap(tofree->ptr, tofree->size);
	if ((tofree + 1)->size)
	{
		ft_memmove(tofree, tofree + 1, (void *)H_FAT + MAX_HEADER(t_fat, S_HEADER_F) - (void *)(tofree + 1));
	}
	else
		ft_bzero(tofree, sizeof (t_fat));
	FAT_SIZE++;
	//voir quand on realou une deuxieme fois
	return (0);
}

void ft_free(void *ptr)
{
	short	type;

	if (!ptr)
	{
		printf("!ptr n existe pas\n");
		return ;
	}
	type = get_type(ptr);
	printf("type %d ptr %p\n", type, ptr);
	if (type == 1 || type == 0)
		free_tny_small(!type ? H_TINY : H_MED, ptr);
	else
		free_fat(ptr);
}
