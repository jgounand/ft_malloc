/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:15:30 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/01 17:25:14 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

short gettype(void *ptr)
{
	if (ptr < (void *)g_mem + getpagesize() * 3 + MAX_TINY)
	{
		printf("FREE TINY\n");
		return (0);
	}
	else if (ptr < (void *)g_mem + getpagesize() * 3 + MAX_TINY + MAX_MED)
	{
		printf("FREE MED\n");
		return (1);
	}
	else
	{
		printf("FREE FAT\n");
		return (2);
	}
}
void ft_free(void *ptr)
{
	short	type;

	type = gettype(ptr);
}
