/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:46:23 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/23 05:02:01 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

t_mem	*g_mem = NULL;

t_mem	*init_mem(void)
{

	if (g_mem)
		return (g_mem);
	g_mem = mmap(NULL, sizeof(t_mem) + getpagesize() * 3 + MAX_TINY + MAX_MED,
			PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (g_mem == NULL)
	{
		write(2, "ERROR\n",6);
		return (NULL);
	}
	ft_bzero(g_mem, sizeof(t_mem) + MAX_TINY + MAX_MED + getpagesize() * 3);
	g_mem->tiny = (t_tny *)(g_mem + 1);
	g_mem->med = (t_med *)(g_mem + getpagesize());
	g_mem->fat = (t_fat *)(g_mem + getpagesize() * 2);
	g_mem->next = NULL;
	return (g_mem);
}

t_node *search_place(t_node *start, size_t lenght, size_t max, char type)
{
	t_node	*current;
	t_node	*next;
	size_t	*free;
	while (current)
	{
		if (!current->size && (next = current + 1))
		{
			
		}
	}
		if ()
		if (tmp->previous && lenght <= tmp->previous->free + tmp->free && type == tmp->type)
		{
				tmp->ptr = tmp->ptr - tmp->previous->free;
				tmp->free -= (lenght - tmp->previous->free);
				tmp->previous->free = 0;
				if (tmp->previous_free)
				{
					tmp->previous_free->next = tmp->next_free;
				tmp->next_free->previous = tmp->previous_free;
				}
				else
				{
					g_mem->free = tmp->next_free;
					tmp->next_free = g_mem->free;
				}
				return (tmp);
		}
		if (lenght <= tmp->free && type == tmp->type)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = start;
	while (tmp)
	{
		if (lenght <= tmp->free)
		{
			total = nodecmpt(&tmp);
			printf("lenght <= tmp->free %lu total\n", total);
				//decaller la structure
				//regarder taile pour ne pas depasser le pagesize
		}
		tmp = tmp->next;
	}
	tmp = start;
	total = 0;
	while (tmp->next)
	{
		total += tmp->size;
		tmp = tmp->next;
	}
	if (max && total + lenght > max)
	{
		printf("error\n");
		return (NULL);
	}
	return (tmp);
}

void	*add_small_node(t_node *start, size_t lenght, size_t max)
{
	t_node *tmp;
	t_node	*new;
	char	type;

	type = start == init_mem()->tiny ? 0 : 1;
	if (!(tmp = search_place(start, lenght, max, type)))
		return NULL;
	if (tmp->free)
	{
		new = tmp;
		printf("new->free %lu\n", new->free);
	}
	else
	{
	new = tmp + 1;
	tmp->next = new;
	new->previous = tmp;
	new->ptr = tmp->end + 1;
	new->end = (void *)tmp->end + lenght;
	new->next = NULL;
	new->type = type;
	}
	new->size = lenght;
	new->hexa = 0;
//	printf("last %p new %p %lu %lu\n",tmp, new , &new - &tmp,sizeof(t_node));
	return (new->ptr + new->hexa);
	}

void	*add_fat_node(t_node *start, size_t lenght)
{
	t_node	*tmp;
	t_node	*new;
	char	type;

	type = start == init_mem()->tiny ? 0 : 1;
	if (!(tmp = search_place(start, lenght, 0 ,type)))
		return NULL;
	if (tmp->free)
	{
		new = tmp;
		new->free = new->free - lenght;
		printf("new->free %lu\n", new->free);
	}
	else
	{
	new = tmp + 1;
	tmp->next = new;
	new->previous = tmp;
	new->end = (void *)tmp->end + lenght;
	new->next = NULL;
	new->type = 3;
	}
	new->size = lenght;
	new->hexa = 0;
	if (!(new->ptr = mmap(NULL, lenght, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)))
		return (NULL);
	//printf("last %p new %p %lu %lu\n",tmp, new , &new - &tmp,sizeof(t_node));
	return (new->ptr);
}
void *ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	if (size <= TINY)
		return (add_small_node(init_mem()->tiny, size, MAX_TINY));
	else if (size <= SMALL)
		return (add_small_node(init_mem()->med, size, MAX_MED));
	else
		return (add_fat_node(init_mem()->fat, size));
	return (NULL);
}
