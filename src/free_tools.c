/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:23:35 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:08:45 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	void *ptr
**	Output:	short [0-3]
**	Purpose:	Get header data
**				Check in whitch part is the pointeur
**				if on 0 => MAX_TINY = TINY
**				if on MAX_TINY => MAX_TINY + MAX_MED = MED
**				if get_fat => FAT
**				else no a pointer
*/

short	get_type(void *ptr)
{
	t_start	*start;

	start = get_start(ptr, 0);
	if (ptr < start->start + MAX_TINY && ptr >= start->start)
		return (0);
	else if (ptr < start->start + MAX_TINY + MAX_MED && ptr >= start->start +
			MAX_TINY)
		return (1);
	else if (get_fat(ptr))
		return (2);
	else
		return (3);
}

/*
**	Input:	t_tny *tofree
**	Output:	bool not begin_data
**	Purpose:	get the header start associate
**				Check  if ptr is the begin of TINY or MED
*/

bool	not_begin_data(t_tny *tofree)
{
	void	*ptr;

	ptr = get_start(tofree->ptr, 0)->start;
	if (ptr == tofree->ptr || (ptr + MAX_TINY) == tofree->ptr)
		return (0);
	return (1);
}

/*
**	Input:	t_tny *tofree
**	Output:	bool diff_data
**	Purpose:	Check  if tofree->ptr and (tofree + 1)->ptr same header start
*/

bool	diff_data(t_tny *tofree)
{
	if (get_start(tofree->ptr, 0)->start ==
			get_start((tofree + 1)->ptr, 0)->start)
		return (0);
	return (1);
}
