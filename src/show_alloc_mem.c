/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:31:21 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/10 15:32:41 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void			show_alloc_mem(void)
{
	size_t	total;

	init_mem();
	total = print_lignes_tymed(0, H_TINY, 1);
	total += print_lignes_tymed(1, H_MED, 1);
	total += print_lignes_fat(H_FAT, 1);
	ft_putstr("\n");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr("\n");
}
