/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:50:22 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_fat	*get_fat(void *ptr)
{
	size_t	node;
	t_fat		*fat;

	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	fat = H_FAT;
	while (node)
	{
		if (ptr == fat->ptr)
		break;
		fat++;
		node--;
	}
	return ((node ? fat : NULL));
}
short	get_type(void *ptr)
{
	t_start	*start;

printf("get type ptr %p\n", ptr);
	start = get_start(ptr, 0);
dprintf(2,"start %p start->start %p\n",start, start->start);
	if (ptr < start->start + MAX_TINY && ptr >= start->start)
		return (0);
	else if (ptr < start->start + MAX_TINY + MAX_MED && ptr >= start->start + MAX_TINY)
		return (1);
	else if ( get_fat(ptr))
	{
		return (2);
	}
	else
	{
		printf("Error free %p doesn't exist\n", ptr);
		exit (76);
	}
}


static bool	not_begin_data(t_tny *tofree)
{
	void	*ptr;

	ptr = get_start(tofree->ptr, 0)->start;
	if (ptr == tofree->ptr || (ptr + MAX_TINY) == tofree->ptr)
		return (0);
	return (1);
}
bool	diff_data(t_tny *tofree)
{
	if (get_start(tofree->ptr, 0)->start == get_start((tofree + 1)->ptr, 0)->start)
	{
		printf("%p == %p return 1\n", get_start(tofree->ptr, 0),get_start((tofree + 1)->ptr, 0));
		return (0);
	}
    printf("%p == %p return 0\n", get_start(tofree->ptr, 0),get_start((tofree + 1)->ptr, 0));
	return (1);
}

t_tny	*ret_node(t_tny	*tofree, void *ptr)
{
	short	type;
	size_t	node;

printf("ret_node get_type %p\n", ptr);
	type = get_type(ptr);
	if (type == 4)
	    return (NULL);
	if (!type)
		node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	else
		node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	printf("nb node %lu\n", node);
while (node)
	{
		if (ptr == tofree->ptr)
			break;
		tofree++;
		node--;
	}
	printf("ret_node ptr %p\n", tofree->ptr);
return	(node ? tofree : NULL);
}

static	void	rm_h_start(t_tny	*node, t_tny	*node1)
{
	t_start	*start;

	start = get_start(node->ptr,0);
	printf("start %p g +1 %p\n", start, g_mem + 1);
	if (start == (t_start *)(g_mem + 1))
		return ;
	ft_memmove(start, start + 1, ((void *)(g_mem + 1) + getpagesize() * S_HEADER_A) - (void *)(start + 1));
	munmap(start->start, MAX_TINY + MAX_MED);
	A_SIZE++;
	if (node < H_MED)
	{
		ft_memmove(node, node + 1, ((void *)H_TINY + MAX_HEADER(t_tny, S_HEADER_T)) - (void *)(node + 1));
		TINY_SIZE++;
	}
	else
	{
		ft_memmove(node, node + 1, (void *)H_MED + MAX_HEADER(t_tny, S_HEADER_M) - (void *)(node + 1));
		MED_SIZE++;
	}
	if (!node1)
		return ;
	if (node1 < H_MED)
	{
		ft_memmove(node1, node1 + 1, ((void *)H_TINY + MAX_HEADER(t_tny, S_HEADER_T)) - (void *)(node1 + 1));
		TINY_SIZE++;
	}
	else
	{
		ft_memmove(node1, node1 + 1, (void *)H_MED + MAX_HEADER(t_tny, S_HEADER_M) - (void *)(node1 + 1));
		MED_SIZE++;
	}
}
//ici ca bug,  changement du ptr
static bool check_header_free(t_tny *tofree)
{
	t_start	*start;
	t_tny	*node;
	void	*ptr;

printf("check_header_free %p\n", tofree->ptr);
if ((size_t)get_start(tofree->ptr,1) <= 1)
	return (0);
	start = get_start(tofree->ptr, 0);
	if (start->start == tofree->ptr)
	{
	printf("0\n");
		node = H_MED;
		ptr = start->start + MAX_TINY;
	}
	else
	{
	printf("1\n");
		node = H_TINY;
		ptr = start->start;
	}
	if (tofree->size == - MAX_TINY)
	{
	printf("before node check_header_free %p\n", ptr);
		node = ret_node(node, ptr);
		//si c est le dernier header ne pas supprimer !!!
		if (!node || node->size == - MAX_TINY)
			rm_h_start(tofree, node);
	}
	return (0);
}

void	try_defragment(t_tny *tofree)
{
	short	type;

printf("try_defragment get_type %p\n", tofree->ptr);
	type = get_type(tofree->ptr);
	printf("tofree + 1 %p\n",(tofree + 1)->ptr);
	printf("0\n");
	if ((tofree + 1)->size < 0)
	{
		printf("tofree->size %d\n", tofree->size);
		if (!diff_data(tofree +1))
		{
			printf("0.1\n");
			tofree->size = (uintptr_t)(tofree + 1)->ptr - (uintptr_t)tofree->ptr;
			tofree->size = -tofree->size + (tofree +1)->size;
			printf("tofree->size %d\n", tofree->size);
		}
		else
		{
			printf("0.2\n");
			tofree->size = -((uintptr_t)(tofree + 1)->ptr - (uintptr_t)tofree->ptr) + (tofree + 1)->size;
			printf("tofree size %d\n", tofree->size);
		}
		size_t size =   (void *)(tofree + 2) - (void *)(type ? H_MED :H_TINY) + MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T));
		printf("size to move %lu\n",size / sizeof(t_tny));
		ft_memmove(tofree + 1, tofree + 2, size);
		printf("tofree + 1)->ptr %p %p\n", (tofree + 1)->ptr, tofree->ptr);
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
			if (!diff_data(tofree))
				(tofree - 1)->size += tofree->size;
			else
				(tofree- 1)->size = -((uintptr_t)(tofree)->ptr - (uintptr_t)(tofree - 1)->ptr) + (tofree)->size;
			size_t size =   (void *)(tofree + 1) - (void *)(type ? H_MED :H_TINY) + MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T));
			ft_memmove(tofree, tofree + 1, size);
			printf("tofree->size %d\n", tofree->size);
			if (!type)
				TINY_SIZE++;
			else
				MED_SIZE++;
		}
	}
	check_header_free(tofree);
}


static void free_tny_small(t_tny *tofree, void *ptr)
{
	printf("before node free_tny_small %p\n", ptr);
	tofree = ret_node(tofree, ptr);
	if (!tofree)
	{
		show_alloc_mem(1);
		printf("error tmp nulli %p\n", ptr);
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
	munmap(tofree->ptr, tofree->size);
	ft_memmove(tofree, tofree + 1, (void *)H_FAT + MAX_HEADER(t_fat, S_HEADER_F) - (void *)(tofree + 1));
	FAT_SIZE++;
	return (0);
}

void ft_free(void *ptr)
{
	short	type;

printf("free ptr %p\n", ptr);
	if (!ptr)
	{
		printf("!ptr n existe pas\n");
		return ;
	}
	type = get_type(ptr);
	printf("\ttype %d ptr %p\n", type, ptr);
	if (type == 1 || type == 0)
		free_tny_small(!type ? H_TINY : H_MED, ptr);
	else
		free_fat(ptr);
}
