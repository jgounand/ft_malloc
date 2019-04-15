/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defragment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:34:14 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 17:26:41 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

/*
**	Input:	t_tny *tofree
**			short type
**	Output:	void
**	Purpose:	Size = diff tofree->ptr and (tofree+1)->ptr and
**	(tofree+1)->size
**				Memove to delete tofree + 1
*/

static void	def_neg_samedata(t_tny **tofree, short type)
{
	size_t	size;

	(*tofree)->size = ((*tofree) + 1)->ptr - (*tofree)->ptr;
	(*tofree)->size = -(*tofree)->size + ((*tofree) + 1)->size;
	size = ((void *)(type ? H_MED : H_TINY) + (sizeof(t_tny)) *
			MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)))
		- (void *)((*tofree) + 2);
	ft_memmove((*tofree) + 1, (*tofree) + 2, size);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
}

/*
**	Input:	t_tny *tofree
**			short type
**	Output:	void
**	Purpose:	Size = MAX of the header - tofree->ptr
**				Memove to delete tofree
*/

static void	def_neg_difdata(t_tny **tofree, short type)
{
	size_t	size;

	if (type == 0)
	(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start_tiny)
				+ getpagesize()) - (*tofree)->ptr);
	if (type == 0)
		(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start_med)
							 + getpagesize()) - (*tofree)->ptr);
	if ((*tofree)->size > -8)
	{
		size = ((void *)(type ? H_MED : H_TINY) + (sizeof(t_tny))
			* MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T)))
			- (void *)((*tofree) + 1);
		ft_memmove((*tofree), (*tofree) + 1, size);
		if (!type)
			TINY_SIZE++;
		else
			MED_SIZE++;
	}
}

/*
**	Input:	t_tny *tofree
**			short type
**	Output:	void
**	Purpose:	if the node + 1 diff data => MAX - tofree->ptr
**					else tofree + 1 ->ptr - tofree->ptr
*/

static void	def_pos(t_tny **tofree, short type)
{
	if (!diff_data(*tofree,type))
		(*tofree)->size = -(((*tofree) + 1)->ptr - (*tofree)->ptr);
	else {
		if (type == 0)
		{
			(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start_tiny)
								 + getpagesize()) - (*tofree)->ptr);

		}
		else {
			(*tofree)->size = -(((void *)(get_start((*tofree)->ptr, 0)->start_med)
								 + getpagesize()) - (*tofree)->ptr);

		}
	}
}

/*
**	Input:	t_tny *tofree
**			short type
**	Output:	void
**	Purpose:	If same data need juste to add the free size
**					else adjut size of the tofree - 1
*/

static void	def_prevneg_samedata(t_tny **tofree, short type)
{
	size_t	size;

	if (!diff_data(*tofree,type))
		((*tofree) - 1)->size += (*tofree)->size;
	else
		((*tofree) - 1)->size = -((*tofree)->ptr - ((*tofree) - 1)->ptr)
			+ (*tofree)->size;
	size = (void *)(type ? H_MED : H_TINY) + sizeof(t_tny) *
		MAX_HEADER(t_tny, (type ? S_HEADER_M : S_HEADER_T))
		- (void *)((*tofree) + 1);
	ft_memmove(*tofree, (*tofree) + 1, size);
	if (!type)
		TINY_SIZE++;
	else
		MED_SIZE++;
}

/*
**	Input:	t_tny *tofree
**	Output:	void
**	Purpose:	Try to fusion 2 free nodes together
*/

void		try_defragment(t_tny *tofree)
{
	short	type;

	type = get_type(tofree->ptr);
	if ((tofree + 1)->size < 0)
	{
		if (!diff_data(tofree,type))
			def_neg_samedata(&tofree, type);
		else
			def_neg_difdata(&tofree, type);
	}
	else
		def_pos(&tofree, type);
	if (not_begin_data(tofree))
	{
		if ((tofree - 1)->size < 0 && !diff_data(tofree - 1,type))
			def_prevneg_samedata(&tofree, type);
	}
}
