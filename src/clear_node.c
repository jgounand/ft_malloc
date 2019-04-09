/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:25:10 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 11:26:13 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	short type
**			size_t lenght
**	Output:	t_infonode node
**	Purpose:	Get the number Header and the start of the header
**				Break if they are no node left or node free > lenght
*/

size_t	get_free_nodeleft(short type, size_t lenght)
{
	t_tny	*tmp;
	size_t	node_left;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE :
	MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!node_left || (tmp->size < 0 && lenght <= (size_t)-tmp->size))
			break ;
		tmp++;
		node_left--;
	}
	return (node_left);
}

/*
**	Input:	short type
**			size_t lenght
**	Output:	t_infonode node
**	Purpose:	Get the number Header and the start of the header
**				Break if they are no node left or node free > lenght
*/

t_tny	*get_free_node(short type, size_t lenght)
{
	t_tny	*tmp;
	size_t	node_left;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE :
	MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!node_left || (tmp->size < 0 && lenght <= (size_t)-tmp->size))
			break ;
		tmp++;
		node_left--;
	}
	return (tmp);
}

/*
**	Input:	short type
**			t_tny **tmp
**	Output:	size_t size
**	Purpose:	Get the position of max and doing the difference
**				beetween tmp->ptr and the max
*/

size_t	get_bytes_cpy(short type, t_tny **tmp)
{
	void	*max;
	size_t	bytes_cpy;

	if (type == 0)
	{
		max = H_TINY + MAX_HEADER(t_tny, S_HEADER_T);
		bytes_cpy = (void *)(max) - (void *)((*tmp) + 1)
		- sizeof(t_tny) * TINY_SIZE;
	}
	else
	{
		max = H_MED + MAX_HEADER(t_med, S_HEADER_M);
		bytes_cpy = (void *)(max) - (void *)((*tmp) + 1)
		- sizeof(t_tny) * MED_SIZE;
	}
	return (bytes_cpy);
}

/*
**	Input:	short type
**	Output:
**	Purpose:	Check if they are a node with size == 0;
**				Delete it
*/

void	check_header_zero(short type)
{
	t_tny	*tmp;
	size_t	bytes_cpy;
	size_t	node_left;

	tmp = type ? H_MED : H_TINY;
	node_left = type ? MAX_HEADER(t_med, S_HEADER_M) - MED_SIZE :
	MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE;
	while (node_left)
	{
		if (!tmp->size)
		{
			bytes_cpy = get_bytes_cpy(type, &tmp);
			remove_header(&tmp, bytes_cpy, type);
			check_header_left();
			return ;
		}
		tmp++;
		node_left--;
	}
}
