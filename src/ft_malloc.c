/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/20 18:21:12 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

t_mem	*init_mem(void)
{
	t_key	*key;

	if (g_mem)
		return (g_mem);
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * 3 + MAX_TINY + MAX_SMALL,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		write(2, "ERROR\n",6);
		return (NULL);
	}
	ft_bzero(g_mem, sizeof(t_mem) + MAX_TINY + MAX_SMALL + getpagesize() * 3);
	key = (t_key *)(g_mem + 1);
	key->key = 125;
	g_mem->tiny = (t_tny *)(key + 1);
	g_mem->med = (t_med *)(g_mem + getpagesize());
	g_mem->fat = (t_fat *)(g_mem + getpagesize() * 2);
	g_mem->next = NULL;
	ft_bzero(g_mem->tiny, sizeof(t_tny));
	ft_bzero(g_mem->med, sizeof(t_med));
	ft_bzero(g_mem->fat, sizeof(t_fat));
	g_mem->tiny->end = g_mem + getpagesize() * 3;
	g_mem->med->end = g_mem + getpagesize() * 3 + getpagesize()* TINY * NB_PAGES;
	g_mem->fat->end = NULL;
	return (g_mem);
}

void	*add_small_node(t_node *start, size_t lenght, size_t max)
{
	t_node	*tmp;
	t_node	new;
	size_t	total;

	total = 0;
	tmp = start;

	while (tmp->next)
	{
	printf("tmp %p next %p\n", tmp, tmp->next);
		total += tmp->size;
		tmp = tmp->next;
	}
	if (total + lenght > max)
	{
		//taille trop grande
		printf("error\n");
		return (NULL);
	}
	tmp->next = &new;
	new.ptr = tmp->end;
	new.size = lenght;
	new.hexa = 0;
	new.end = tmp->end + lenght;
	new.next = NULL;
//	printf("new %p next %p\n", new, new->next);
	return (new.ptr);
	}

void *ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size <= TINY)
		return (add_small_node(init_mem()->tiny, size, MAX_TINY));
	else if (size <= SMALL)
	;//	return (add_small_node(init_mem()->small, size, init_mem()->max_small));
	else
		;
	return (NULL);
}
