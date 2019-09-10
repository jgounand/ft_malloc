/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:26:21 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/10 15:20:39 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void		init_data_firsttime(void)
{
	t_tny			*tny;
	t_med			*med;
	t_start			*start;
	unsigned short	i;

	tny = H_TINY + 1;
	med = H_MED + 1;
	start = (t_start *)(g_mem + 1) + 1;
	i = 0;
	while (i++ < 0)
	{
		start->start_tiny = mem_data(1);
		start->start_med = mem_data(1);
		A_SIZE--;
		tny->ptr = start->start_tiny;
		tny->size = -getpagesize();
		TINY_SIZE--;
		med->ptr = start->start_med;
		med->size = -getpagesize();
		MED_SIZE--;
		tny++;
		med++;
		start++;
	}
}
