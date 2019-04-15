/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 12:27:24 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/08 18:29:45 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_tny *node
**			size_t size
**	Output:	short [0-2]
**	Purpose:	return 0 => place too fit the new size on the node
**				return 2 => place too fit the new size with node + 1
**				return 1 => no place to fit the new size => need malloc
*/

static short	need_alloc(t_tny *node, size_t size, bool type)
{
	size_t	current_lenght;

	if (!diff_data(node,type))
		current_lenght = (node + 1)->ptr - (void *)node->ptr;
	else
		current_lenght = node->size;
	if (current_lenght > size + 1)
		return (0);
	else if (!diff_data(node,type) && (node + 1)->size < 0 && current_lenght
		- (node + 1)->size > size + 1)
		return (2);
	return (1);
}

/*
**	Input:	void *ptr
**			size_t size
**			short type
**	Output:	void *new_ptr
**	Purpose:	check if need to alloc
**					need_alloc 1 => need_alloc  function r_mall_free()
**					need_alloc 2 => have the place to fit with node + 1
**				Add node free if size > 16 (addr every % 8)
*/

static void		*ft_realloc_small(void *ptr, size_t size, short type)
{
	t_tny	*node;
	short	need_all;

	node = !type ? H_TINY : H_MED;
	if (!(node = ret_node(node, ptr)))
	{
	    ft_putendl("10");
		return (NULL);
	}
	if ((need_all = need_alloc(node, size, type)) == 1){

		ft_putendl("11");
		return (r_mall_free(node, size));
	}
	else if (need_all == 2)
	{
		ft_putendl("12");
		return (r_with_node1(&node, size, type));
	}
	else
	{
		ft_putendl("13");
		return (r_with_node(&node, size, type));
	}
}

/*
**	Input:	void *ptr
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	check if ptr exist
**				malloc new size
**				cpy the max possible
**				free the old ptr
*/

static void		*ft_realloc_fat(void *ptr, size_t size)
{
	t_fat	*fat;
	void	*new;
	size_t	c_lenght;

	if (!(fat = get_fat(ptr)))
		return (NULL);
	c_lenght = fat->size;
	new = malloc(size);
	if (size < c_lenght)
		ft_memcpy(new, ptr, size);
	else
		ft_memcpy(new, ptr, c_lenght);
	free(ptr);
	return (new);
}

/*
**	Input:	void *ptr
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	check if ptr exist and if size > 0
**				get the type [0-2]
**					type 0 || 1 : realloc header tiny / small
**					type 2 : realloc header fat
*/

void			*realloc(void *ptr, size_t size)
{
	short	type;

	ft_putstr("realloc size :");
	ft_putnbr(size);
	ft_putstr("\n");
	if (size <= 0)
		return (NULL);
	if (!ptr)
		return (malloc(size));
	type = get_type(ptr);
	if (type == 0 || type == 1)
		return (ft_realloc_small(ptr, size, type));
	else if (type == 2)
		return (ft_realloc_fat(ptr, size));
	else
		return (NULL);
}
