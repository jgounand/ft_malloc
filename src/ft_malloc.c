/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/16 17:35:46 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

t_mem	*init_mem(void)
{
	if (g_mem)
		return (g_mem);
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
	g_mem->tiny->next = NULL;
	g_mem->tiny->end = g_mem->tiny + 1; 
	g_mem->max_tiny = getpagesize() * TINY * 100;
	g_mem->small = (t_node *)g_mem->max_tiny + 1;
	g_mem->max_small = getpagesize() * SMALL * 100;
	g_mem->large = NULL;
	g_mem->next = NULL;
	return (g_mem);
}

void	*add_small_node(t_node *start, size_t lenght, size_t max)
{
	t_node	*tmp;
	t_node	*new;
	size_t	total;

	total = 0;
	tmp = start;
	while (tmp->next)
	{
	printf("tmp %p next %p\n", tmp, tmp->next);
		tmp = tmp->next;
	}
	if (tmp->end + lenght > start + max)
	{
		//taille trop grande
		return (NULL);
	}
	new = tmp->end;
	tmp->next = new;
	new->end = new + lenght + 1;
	new->next = NULL;
	printf("new %p next %p\n", new, new->next);
	return (new + 1);
}

void *ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size <= TINY)
		return (add_small_node(init_mem()->tiny, size, init_mem()->max_tiny));
	else if (size <= SMALL)
		;
	else
		;
	return (NULL);
}
