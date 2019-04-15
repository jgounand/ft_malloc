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
		dprintf(2,"debug_check_max_header");
			dprintf(2, "TINY_SIZE %lu MED_SIZE %lu\n", TINY_SIZE, MED_SIZE);
			show_alloc_mem();
			exit (3);
	}
}
short	get_type_debug(void *ptr)
{
	t_start	*start;

	short fd2 = 2;
	dprintf(fd2,"get type ptr %p\n", ptr);
	start = get_start(ptr, 0);
	dprintf(fd2,"start %p\nstart->start %p\nstart->start + MAX_TINY %p\n",start, start->start, start->start + MAX_TINY);
	dprintf(fd2,"ptr < start + MAXTINY %u\n",ptr < start->start + MAX_TINY );
	dprintf(fd2,"ptr >= start->start %u\n",ptr >= start->start);
	if (ptr < start->start + MAX_TINY && ptr >= start->start)
		return (0);
	else if (ptr < start->start + MAX_TINY + MAX_MED && ptr >= start->start + MAX_TINY)
		return (1);
	else if (0)
	{
		return (2);
	}
	else
	{
		printf("Error free %p doesn't exist\n", ptr);
		exit (76);
	}
}

void check_ptr_prensent(char **tab, size_t size)
{
	size_t i = 0;
	short type;
	t_tny *node;

	while (i <= size)
	{
		type = get_type(tab[i]);

		if (!type)
			node = H_TINY;
		else
			node = H_MED;
		if (tab[i] && !ret_node(node, tab[i]) && !get_fat(tab[i]))
		{
			dprintf(2,"error check ptr present\n");
			dprintf(2,"type %u\n",type);

			dprintf(2,"type check %u\n",get_type_debug(tab[i]));
			show_alloc_mem();
			printf("i : %lu ptr : %p\n",i,tab[i]);
			exit(69);
		}
		i++;
	}
}

