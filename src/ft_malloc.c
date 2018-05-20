/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/20 13:53:06 by jgounand         ###   ########.fr       */
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
	return (ptr);
}

void	*add_node_free(t_tny *tmp, void *ptr, bool type)
{
	ft_memmove(tmp + 2, tmp + 1,(void *)(type ? H_MED : H_TINY) + MAX_HEADER(t_tny, 0 + (type ? S_HEADER_M : S_HEADER_T)) - (void *)(tmp + 1));
	(tmp + 1)->ptr = ptr;
	(tmp + 1)->size = -((uintptr_t)(tmp + 2)->ptr - (uintptr_t)(tmp + 1)->ptr);
	return (NULL);
}

void	*add_small(short type, size_t lenght)
{
	t_tny *tmp;
	size_t	node;

	debug_check_MAX_HEADER();
	if (!(g_mem->max_size[(int)type]))
	{
		dprintf(2,"il faut realouer !! type nbr %d %lu\n", type, g_mem->max_size[(int)type] - 1);
		add_mem_header(type);
	}
	if (type == 1)
	{
		tmp = H_MED;
		node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	}
	else
	{
		tmp = H_TINY;
		node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	}

	dprintf(2,"\t\t\t\ttype %d %p node %lu\n", type, tmp, node);

	while (node)
	{
		if (tmp->size < 0 && lenght <= (size_t)-tmp->size)
			break ;
		if (!node)
			break ;
		tmp++;
		node--;
	}
	dprintf(2,"node %lu tmp->size %d lenght %lu\n", node, tmp->size, lenght);
	//printf("10 lenght %lu => %lu type %d %d node %llu\n",lenght ,((tmp + 1)->ptr - get_addr(tmp->ptr + lenght + 1)), type, (type ? TINY + 1 : 1), node) ;
	//		printf("+");
	if (!node)
	{
		if (!(tmp-1)->ptr)
		{
			show_alloc_mem();
			dprintf(2, "tmp -1 ptr %p, tmp-2 ptr %p tmp -3 ptr %p\n", (tmp - 1)->ptr, (tmp -2)->ptr, (tmp -3)->ptr);
			exit (9);
		}
	if (!(g_mem->max_size[(int)type] - 2))
	{
		add_mem_header(type);
	//	exit (999);
		return (add_small(type, lenght));
		//ici plus de place need more header et plus de data
	}
		dprintf(2,"1\n");
		dprintf(2,"\til faut realouer data !! type %d\n", type);
		tmp->ptr = get_addr(get_new_data((tmp - 1)->ptr)->start + (type ? MAX_TINY : 0));
		printf("get_start->start %p ptr- %p\n", tmp->ptr, get_start(tmp->ptr, 0)->start + MAX_TINY);
		tmp->size = - MAX_MED;
		node++;
		dprintf(2, "tmp->ptr %p size %d\n", tmp->ptr, tmp->size);
		if (!type)
			TINY_SIZE--;
		else
			MED_SIZE--;
	//	show_alloc_mem();
	}
		if (!node - 1)
		{
			dprintf(2,"2\n");
			dprintf(2,"\ttmp size %d ptr %p\n", (tmp)->size, tmp->ptr);
			(tmp + 1)->ptr = get_addr(tmp->ptr + lenght + 1);
			dprintf(2, "(tmp+1)->ptr %p max %p\n",(tmp+1)->ptr, (get_start(tmp->ptr, 0)->start + (type ? MAX_TINY + MAX_MED : MAX_TINY)));
			(tmp + 1)->size = (tmp + 1)->ptr - (get_start(tmp->ptr, 0)->start + (type ? MAX_TINY + MAX_MED : MAX_TINY));
			dprintf(2,"\ttmp+1 size %d ptr %p\n", (tmp +1)->size, (tmp +1)->ptr);
			if ((tmp + 1)->size > 0)
			{
				show_alloc_mem();
				exit(22);
			}
		}
		else if (-tmp->size - lenght >= (type ? SMALL : 8))
		{
			// ajouter un free apres tmp et le mmemove
			dprintf(2,"3\n");
			dprintf(2,"\tajouter free apres\n");
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
			exit (1);
		}
		tmp->size = lenght;
		if (!type)
			TINY_SIZE--;
		else
			MED_SIZE--;
	clear_header();
		return (tmp->ptr);
	}

	void	*add_fat(size_t lenght)
{
	t_fat *tmp;
	size_t	node;

	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	printf("ADD FAT\n");
	//tmp = type == 1? H_MED : H_TINY;
	if (!g_mem->max_size[2])
	{
		printf("il faut realouer !!\n");
		add_mem_header(2);
	}
	tmp = H_FAT; 
	printf("type %p tmp->size %lu \n", tmp, tmp->size);
	while (node--)
		tmp++;
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
