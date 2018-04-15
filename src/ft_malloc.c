/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/15 21:21:37 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_malloc	g_mem;

void *malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	if (!size)
		return (ptr);
	if (size <= TINY)
		;
	else if (size <= SMALL)
		;
	else if (size <= LARGE)
		;
	else
		;
	return (ptr);
}
