/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 14:21:06 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 13:42:28 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(const char *str)
{
	int	index;

	if (str)
	{
		index = 0;
		while (str[index] != '\0')
		{
			ft_putchar(str[index]);
			index++;
		}
	}
}
