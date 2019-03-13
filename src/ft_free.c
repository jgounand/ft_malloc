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

/**
 **	Input:	void *ptr
 **	Output:	t_fat *node
 **	Purpose:	Check on Header fat if ptr exist
 */

t_fat		*get_fat(void *ptr)
{
	size_t	node;
	t_fat	*fat;

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

/**
 **	Input:	void *ptr
 **	Output:	short [0-3]
 **	Purpose:	Get header data
 **				Check in whitch part is the pointeur
 **				if on 0 => MAX_TINY = TINY
 *				if on MAX_TINY => MAX_TINY + MAX_MED = MED
 *				if get_fat => FAT
 *				else no a pointer
 */

short	get_type(void *ptr)
{
	t_start	*start;

	start = get_start(ptr, 0);
	if (ptr < start->start + MAX_TINY && ptr >= start->start)
		return (0);
	else if (ptr < start->start + MAX_TINY + MAX_MED && ptr >= start->start + MAX_TINY)
		return (1);
	else if ( get_fat(ptr))
		return (2);
	else
		return (3);
}

/**
 **	Input:	t_tny *tofree
 **	Output:	bool not begin_data
 **	Purpose:	get the header start associate
 **				Check  if ptr is the begin of TINY or MED
 */

static bool	not_begin_data(t_tny *tofree)
{
	void	*ptr;

	ptr = get_start(tofree->ptr, 0)->start;
	if (ptr == tofree->ptr || (ptr + MAX_TINY) == tofree->ptr)
		return (0);
	return (1);
}

/**
 **	Input:	t_tny *tofree
 **	Output:	bool diff_data
 **	Purpose:	Check  if tofree->ptr and (tofree + 1)->ptr same header start
 */

bool	diff_data(t_tny *tofree)
{
	if (get_start(tofree->ptr, 0)->start == get_start((tofree + 1)->ptr, 0)->start)
		return (0);
	return (1);
}

/**
 **	Input:	t_tny *tofree
 **	Output:	bool diff_data
 **	Purpose:	Check  if tofree->ptr and (tofree + 1)->ptr same header start
 */

t_tny	*ret_node(t_tny	*tofree, void *ptr)
{
	short	type;
	size_t	node;

	type = get_type(ptr);
	if (type == 4)
		return (NULL);
	if (!type)
		node = MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	else
		node = MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE;
	while (node)
	{
		if (ptr == tofree->ptr)
			break;
		tofree++;
		node--;
	}
	return	(node ? tofree : NULL);
}

/**
 **	Input:	t_tny *tofree
 **			short type
 **	Output:	void
 **	Purpose:	Size = diff tofree->ptr and (tofree+1)->ptr and (tofree+1)->size 
 **				Memove to delete tofree + 1
 */

void def_neg_samedata(t_tny **tofree, short type)
{
	size_t	size;

	(*tofree)->size = ((*tofree) + 1)->ptr - (*tofree)->ptr;
	(*tofree)->size = -(*tofree)->size + ((*tofree) +1)->size;
	size = ((void *)(type ? H_MED :H_TINY) + (sizeof(t_tny)) *
			MAX_HEADER(t_tny,(type ? S_HEADER_M : S_HEADER_T)))
		- (void *)((*tofree) + 2) ;
	ft_memmove((*tofree) + 1, (*tofree) + 2, size);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
}

/**
 **	Input:	t_tny *tofree
 **			short type
 **	Output:	void
 **	Purpose:	Size = MAX of the header - tofree->ptr
 **				Memove to delete tofree
 */

void def_neg_difdata(t_tny **tofree, short type)
{
	size_t	size;
	(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start) + MAX_TINY  + (type ? MAX_MED : 0)) - (*tofree)->ptr);
	if ((*tofree)->size > -8)
	{
		size = ((void *)(type ? H_MED :H_TINY) + (sizeof(t_tny)) * MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T))) - (void *)((*tofree) + 1) ;
		ft_memmove((*tofree), (*tofree) + 1, size);
		if (!type)
			TINY_SIZE++;
		else
			MED_SIZE++;
	}
}

/**
 **	Input:	t_tny *tofree
 **			short type
 **	Output:	void
 **	Purpose:	if the node + 1 diff data => MAX - tofree->ptr
 **					else tofree + 1 ->ptr - tofree->ptr
 */

void def_pos(t_tny **tofree, short type)
{
	if (!diff_data((*tofree)))
		(*tofree)->size = -(((*tofree) + 1)->ptr - (*tofree)->ptr);
	else
		(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start) + MAX_TINY  + (type ? MAX_MED : 0)) - (*tofree)->ptr);
}

/**
 **	Input:	t_tny *tofree
 **			short type
 **	Output:	void
 **	Purpose:	If same data need juste to add the free size
 **					else adjut size of the tofree - 1
 */

void	def_prevneg_samedata(t_tny **tofree, short type)
{
size_t	size;

	if (!diff_data(*tofree))
		((*tofree) - 1)->size += (*tofree)->size;
	else
		((*tofree)- 1)->size = -((*tofree)->ptr - ((*tofree) - 1)->ptr) + (*tofree)->size;
	size =  (void *)(type ? H_MED :H_TINY) + sizeof(t_tny) * MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)) - (void *)((*tofree) + 1) ;
	ft_memmove(*tofree, (*tofree) + 1, size);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
}

/**
 **	Input:	t_tny *tofree
 **	Output:	void
 **	Purpose:	Try to fusion 2 free nodes together
 */

void	try_defragment(t_tny *tofree)
{
	short	type;

	type = get_type(tofree->ptr);
	if ((tofree + 1)->size < 0)
	{
		if (!diff_data(tofree))
			def_neg_samedata(&tofree, type);
		else
			def_neg_difdata(&tofree,type);
	}
	else
		def_pos(&tofree,type);
	if (not_begin_data(tofree))
	{
		if ((tofree -1)->size < 0 && !diff_data(tofree - 1))
		def_prevneg_samedata(&tofree,type);
	}
}

/**
 **	Input:	t_tny *tofree
**			void *ptr
 **	Output:	void
 **	Purpose:	Check if the ptr exist on the Header and free it
 */

static void free_tny_small(t_tny *tofree, void *ptr)
{
	tofree = ret_node(tofree, ptr);
	if (!tofree)
		return;
	else
		try_defragment(tofree);
}

/**
 **	Input:	void *ptr
 **	Output:	int
 **	Purpose:	Check if the ptr exist on the Header
 **				alloc new size
 **				cpy the maximum
 **				free ptr
 */

static int	free_fat(void *ptr)
{
	t_fat	*tofree;

	tofree = get_fat(ptr);
	if (!tofree)
		return (0);
	munmap(tofree->ptr, tofree->size);
	size_t size =  (void *)(H_FAT) + sizeof(t_tny) * MAX_HEADER(t_fat, S_HEADER_F) - (void *)(tofree + 1) ;
	ft_memmove(tofree, tofree + 1, size);
	FAT_SIZE++;
	return (0);
}

/**
 **	Input:	void *ptr
 **	Output:
 **	Purpose:	Check if the type and free 
 */

void ft_free(void *ptr)
{
	short	type;

	if (!ptr)
		return ;
	type = get_type(ptr);
	if (type == 1 || type == 0)
		free_tny_small(!type ? H_TINY : H_MED, ptr);
	else if (type == 2)
		free_fat(ptr);
}
