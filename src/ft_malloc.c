/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/15 22:36:04 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	g_mem = NULL;

t_mem	*init_mem(void)
{
	void	*new;

	if (g_mem)
		return (g_mem);
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * TINY * 100 +
			getpagesize() *SMALL * 100,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		//error ERRNO
		return (NULL);
	}
	g_mem->tiny = g_mem + 1;
	g_mem->max_tiny = g_mem->tiny + getpagesize() * TINY * 100;
	g_mem->small = g_mem->max_tiny + 1;
	g_mem->max_small = g_mem->small + getpagesize() * SMALL * 100;
	g_mem->large = NULL;
}

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
