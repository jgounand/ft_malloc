/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_addrhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:11:43 by jgounand          #+#    #+#             */
/*   Updated: 2019/04/09 11:13:11 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_malloc.h"

void	print_addrhex(int p)
{
	char	*str;
	char	result[9];
	short	i;

	i = 0;
	ft_bzero(result, 9);
	ft_memset(result, '0', 8);
	str = "0123456789ABCDEF";
	while (p)
	{
		result[i] = (str[p % 16]);
		p /= 16;
		i++;
	}
	ft_putstr("0x");
	if (result[8] == '0')
		result[8] = '\0';
	ft_putstr(ft_strrev(result));
}
