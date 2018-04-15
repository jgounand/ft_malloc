/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:32:29 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 09:22:20 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;
	char	*result;

	result = NULL;
	tmp = (char *)s;
	while (*tmp)
	{
		if (*tmp == (char)c)
			result = tmp;
		tmp++;
	}
	if (*tmp == (char)c)
		result = tmp;
	return (result);
}
