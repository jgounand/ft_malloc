/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 09:01:04 by jgounand          #+#    #+#             */
/*   Updated: 2017/12/19 12:04:49 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_b(const char *s, int c)
{
	char *tmp;

	tmp = (char *)s + ft_strlen(s) - 1;
	while (*tmp)
	{
		if (*tmp == (char)c)
			return (tmp);
		tmp--;
	}
	if (*tmp == (char)c)
		return (tmp);
	return (NULL);
}
