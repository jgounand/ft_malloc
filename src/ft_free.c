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
