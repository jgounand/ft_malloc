/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 12:27:24 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:58:23 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/**
**	Input:	t_tny *node
**			size_t size
**	Output:	short [0-2]
**	Purpose:	return 0 => place too fit the new size on the node
**				return 2 => place too fit the new size with node + 1
**				return 1 => no place to fit the new size => need malloc
*/

static short	need_alloc(t_tny *node, size_t size)
{
	size_t	current_lenght;

	if (!diff_data(node))
		current_lenght = (node + 1)->ptr - (void *)node->ptr;
	else
		current_lenght = node->size;
	if (current_lenght > size + 1)
		return (0);
	else if (!diff_data(node) && (node + 1)->size < 0 && current_lenght
		- (node + 1)->size > size + 1)
		return (2);
	return (1);
}

/**
**	Input:	t_tny *node
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	malloc size
**				cpy max size possible of node->ptr
**				free node->ptr
*/

static void		*r_mall_free(t_tny *node, size_t size)
{
	void	*new_ptr;
	t_tny	tmp;

		tmp.size = node->size;
		tmp.ptr = node->ptr;
		new_ptr = ft_malloc(size);
		ft_memcpy(new_ptr, node->ptr, (size < (size_t)tmp.size ? size : tmp.size));
		ft_free(tmp.ptr);
		return (new_ptr);
}

/**
**	Input:	t_tny **node
**			size_t size
**			short type
**	Output:	void *same_ptr
**	Purpose:	Place to fit the realloc with node + 1
**				Save the size beetwen node->ptr and (node+1)->ptr
**					and (node+1)->size
**				Dell the node + 1,
**				Add node free if size > 8 (addr every % 8)
*/

static void		*r_with_node1(t_tny **node, size_t size, short type)
{
	size_t c_lenght;

		c_lenght = ((*node) + 1)->ptr - (*node)->ptr - ((*node) + 1)->size;
		ft_memmove((*node) + 1, (*node) + 2, ((void *)(type ? H_MED :H_TINY) +
		sizeof(t_tny) * MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)) -
		(void *)((*node) + 2)));
		(*node)->size = size;
		if (c_lenght - size > 8)
			add_node_free(*node, get_addr((*node)->ptr + size + 1), type);
		else
		{
			if (type)
				MED_SIZE++;
			else
				TINY_SIZE++;
		}
		return ((*node)->ptr);
}

/**
**	Input:	t_tny **node
**			size_t size
**			short type
**	Output:	void *same_ptr
**	Purpose:	Place to fit the realloc with node
**				Save the size beetwen node->ptr and (node+1)->ptr
**				Add node free if size > 8 (addr every % 8)
**				Add size HEADER if add_free
*/

static void		*r_with_node(t_tny **node, size_t size, short type)
{
		long	size_free = 0;
		void	*ptr;

		if (diff_data(*node))
			size_free = (*node)->size;
		else
			size_free = ((*node) + 1)->ptr - (void *)(*node)->ptr;
		(*node)->size = size;
		ptr = (*node)->ptr;
		if (size_free - size > 8)
		{
			add_node_free((*node), get_addr((*node)->ptr + size + 1), type);
			if (!type)
				TINY_SIZE--;
			else
				MED_SIZE--;
			ptr = (*node)->ptr;
			check_header_left();
		}
		return (ptr);
}

/**
**	Input:	void *ptr
**			size_t size
**			short type
**	Output:	void *new_ptr
**	Purpose:	check if need to alloc
**					need_alloc 1 => need_alloc  function r_mall_free()
**					need_alloc 2 => have the place to fit with node + 1
**				Add node free if size > 8 (addr every % 8)
*/

static void		*ft_realloc_small(void *ptr, size_t size, short type)
{
	t_tny	*node;
	short	need_all;

	node = !type ? H_TINY : H_MED;
	if (!(node = ret_node(node, ptr)))
		return(NULL);
	if ((need_all = need_alloc(node, size)) == 1)
		return (r_mall_free(node,size));
	else if (need_all == 2)
		return (r_with_node1(&node,size,type));
	else
		return (r_with_node(&node,size,type));
}

/**
**	Input:	void *ptr
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	check if ptr exist
**				malloc new size
**				cpy the max possible
**				free the old ptr
*/

static void			*ft_realloc_fat(void *ptr, size_t size)
{
	t_fat	*fat;
	void	*new;
	size_t	c_lenght;

	if (!(fat = get_fat(ptr)))
		return (NULL);
	c_lenght = fat->size;
	new = ft_malloc(size);
	if (size < c_lenght)
		ft_memcpy(new, ptr, size);
	else
		ft_memcpy(new, ptr, c_lenght);
	ft_free(ptr);
	return (new);
}

/**
**	Input:	void *ptr
**			size_t size
**	Output:	void *new_ptr
**	Purpose:	check if ptr exist and if size > 0
**				get the type [0-2]
**					type 0 || 1 : realloc header tiny / small
**					type 2 : realloc header fat
*/

void			*ft_realloc(void *ptr, size_t size)
{
	short	type;

	if (size <= 0 || !ptr)
	{
		if (ptr)
			ft_free(ptr);
		return (NULL);
	}
	type = get_type(ptr);
	if (type == 0 || type == 1)
		return (ft_realloc_small(ptr, size, type));
	else if (type == 2)
		return (ft_realloc_fat(ptr, size));
	else
		return (NULL);
}
