/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:32:04 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 14:29:50 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned long	index;

	if (n == 0)
		return (1);
	index = 1;
	if (s1 && s2)
	{
		while (*s1 == *s2)
		{
			if ((*s1 == '\0' && *s2 == '\0') || n == index)
				return (1);
			s1++;
			s2++;
			index++;
		}
	}
	return (0);
}
