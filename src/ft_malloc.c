/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:29:43 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem		*g_mem = NULL;

/*
**	Input:	t_tny *tmp
**			void *ptr
**			bool type
**	Output:	void* NULL
**	Purpose:	Get size beetwen (tmp + 1) and end
**				Push header tmp + 1 to have the place to put the need node free
**				if same data tmp + 1 and tmp + 2 size = diff ptr tmp1 and tmp2
**				else size = MAX - (tmp + 1)->ptr
**				if new size == 0 => remove the header
*/

void		*add_node_free(t_tny *tmp, void *ptr, bool type)
{
	size_t bytes_cpy;

	bytes_cpy = push_header(&tmp, type);
	(tmp + 1)->ptr = ptr;
	if (!diff_data(tmp + 1,type))
		(tmp + 1)->size = -((tmp + 2)->ptr - (tmp + 1)->ptr);
	else
	{
	    if (type == 0)
        {

	    	(tmp + 1)->size = -(((void *)(get_start((tmp + 1)->ptr, 0)->start_tiny)
								 + getpagesize()) - (tmp + 1)->ptr);
        }
	    else
		{
			(tmp + 1)->size = -(((void *)(get_start((tmp + 1)->ptr, 0)->start_med)
								 + getpagesize()) - (tmp + 1)->ptr);
		}
		if (!(tmp + 1)->size)
			remove_header(&tmp, bytes_cpy, type);
	}
	return (NULL);
}

static bool	add_small_check_error_routine(int type, size_t lenght)
{
	short	error;

	if ((error = check_header_left()) == 1)
		add_small(type, lenght);
	if (error == 2)
		return (1);
	add_rm_header(0, type);
	if (check_header_left() == 2)
		return (1);
	return (0);
}

/*
**	Input:	short type
**			size_t lenght
**	Output: void* ptr
**	Purpose:	Find a node with the place to fit the lenght
**				Else add new data zone and try again
**				Save ptr if they are update of the size Header during proscess
**				The last header need to be a free node, Add data zone if they
**				are not the place to add a free node
**				if nothing of that happen i dont need to increment header
*/

void		*add_small(short type, size_t lenght)
{
	void	*new;
	t_tny	*node;
	size_t	node_left;
	short	error;

	if ((error = check_header_left()))
		return (error == 1 ? add_small(type, lenght) : NULL);
	node = get_free_node(type, lenght);
	node_left = get_free_nodeleft(type, lenght);
	if (!node_left)
	{
		add_mem_data(&node, type, 0);
		return (add_small(type, lenght));
	}
	new = node->ptr;
	if (!(node_left - 1) && -node->size - lenght < 16)
		add_mem_data(&node, type, 1);
	else if (-node->size - lenght > 16)
		add_node_free(node, get_addr(node->ptr + lenght + 1), type);
	else
		add_rm_header(1, type);
	node->size = lenght;
	if (add_small_check_error_routine(type, lenght))
		return (NULL);

	return (new);
}

/*
**	Input:	size_t lenght
**	Output: void *ptr
**	Purpose:	Check if they are place on headers => add_mem_header
**				Allez sur la derniere node
**				Mmap la taille
*/

static void	*add_fat(size_t lenght)
{
	t_fat	*tmp;
	size_t	node;

	if (check_header_left() == 2)
		return (NULL);
	node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	tmp = H_FAT;
	while (node--)
		tmp++;
	tmp->ptr = mmap(NULL, lenght, PROT_READ | PROT_WRITE, MAP_ANON |
	MAP_PRIVATE, -1, 0);
	tmp->size = lenght;
	FAT_SIZE--;
	return (tmp->ptr);
}

/*
**	Input:	size_t lenght
**	Output: void *ptr
**	Purpose:	Init global and call the right function depend of the size
*/

void		*malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	if (!init_mem())
		return (NULL);
	if (size <= TINY)
		return (add_small(0, size));
	else if (size <= SMALL)
		return (add_small(1, size));
	else
		return (add_fat(size));
}
