/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:32:58 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 09:21:10 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*tmp;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	tmp = ft_strnew(len);
	if (!tmp)
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[start];
		i++;
		start++;
	}
	return (tmp);
}
