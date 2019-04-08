/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:30:21 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/08 18:32:34 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_tny **tmp
**			short type
**	Output:	size_t bytes_cpy
**	Purpose:	Get size beetwen MAX position header and the current + 1
**				Move tmp + 1 => tmp + 2 to have the place to add the free node
*/

size_t	push_header(t_tny **tmp, short type)
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
	ft_memmove((*tmp) + 2, (*tmp) + 1, bytes_cpy);
	return (bytes_cpy);
}

/*
**	Input:	t_tny **tmp
**			short type
**			size_t bytes_cpy
**	Output:	size_t bytes_cpy
**	Purpose:	Move tmp + 2 => tmp + 1 to delete the node tmp + 1
*/

size_t	remove_header(t_tny **tmp, size_t bytes_cpy, short type)
{
	ft_memmove((*tmp) + 1, (*tmp) + 2, bytes_cpy);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
	return (bytes_cpy);
}
