/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 17:09:45 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/18 17:11:12 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	debug_check_MAX_HEADER(void)
{
	if (TINY_SIZE > 300 || MED_SIZE > 300)
		{
			dprintf(2, "TINY_SIZE %lu MED_SIZE %lu\n", TINY_SIZE, MED_SIZE);
		//	show_alloc_mem();
			exit (3);
	}
}
