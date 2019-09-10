/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 12:11:04 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/10 15:31:37 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

static void		print_ligne_alloc(void *ptr, long size)
{
	print_addrhex((uint32_t)ptr);
	ft_putstr(" - ");
	if (size >= 0)
		print_addrhex((uint32_t)ptr + size);
	else
		print_addrhex((uint32_t)ptr - size);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets ");
}

static void		print_type(bool type)
{
	if (type == 0)
		ft_putstr("TINY : ");
	if (type == 1)
		ft_putstr("SMALL : ");
}

size_t			print_lignes_tymed(short type, t_tny *node, bool all)
{
	size_t	nb_node;
	size_t	total;

	total = 0;
	print_type(type);
	nb_node = type == 0 ? MAX_HEADER(t_tny, S_HEADER_T) - TINY_SIZE :
			MAX_HEADER(t_tny, S_HEADER_M) - MED_SIZE;
	if (!nb_node)
		return (0);
	print_addrhex((uint32_t)node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0 || all)
		{
			print_ligne_alloc(node->ptr, node->size);
			total += node->size;
			ft_putstr("\n");
		}
		node++;
	}
	return (total);
}

size_t			print_lignes_fat(t_fat *node, bool all)
{
	size_t	nb_node;
	size_t	total;

	total = 0;
	nb_node = MAX_HEADER(t_fat, S_HEADER_F) - FAT_SIZE;
	if (nb_node == 0)
		return (0);
	ft_putstr("FAT : ");
	print_addrhex((uint32_t)node->ptr);
	ft_putstr("\n");
	while (nb_node--)
	{
		if (node->size > 0 || all)
		{
			print_ligne_alloc(node->ptr, node->size);
			ft_putstr("\n");
			total += node->size;
		}
		node++;
	}
	return (total);
}

size_t			print_lignes_headers(void)
{
	size_t	nb_node;
	t_start	*start;

	start = (t_start *)(g_mem + 1);
	nb_node = MAX_HEADER(t_start, S_HEADER_A) - A_SIZE;
	ft_putstr("HEADER : --------------------------------------------------");
	ft_putstr("\n");
	while (nb_node--)
	{
		print_addrhex((uint32_t)start->start_tiny);
		ft_putstr("  -   ");
		print_addrhex((uint32_t)start->start_med);
		ft_putstr("\n");
		start++;
	}
	return (1);
}
