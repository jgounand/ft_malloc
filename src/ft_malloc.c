/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/16 14:02:16 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

t_mem	*init_mem(t_mem *previous)
{
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * TINY * 100 +
			getpagesize() *SMALL * 100,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		//error ERRNO
		write(2, "ERROR\n",6);
		return (NULL);
	}
	g_mem->tiny = (t_node *) (g_mem + 1);
	g_mem->max_tiny = getpagesize() * TINY * 100;
	g_mem->small = (t_node *)g_mem->max_tiny + 1;
	g_mem->max_small = getpagesize() * SMALL * 100;
	g_mem->large = NULL;
	g_mem->next = NULL;
	(void)previous;
	return (g_mem);
}

void	*add_small_node(t_node *start, size_t lenght, size_t max)
{
	t_node *tmp;

	tmp = start;
	while (tmp)
	{

	}
}

void *malloc(size_t size)
{
	if (!g_mem)
		init_mem(NULL);
	if (!size)
		return (NULL);
	if (size <= TINY)
		;
	else if (size <= SMALL)
		;
	else
		;
	return (NULL);
}
