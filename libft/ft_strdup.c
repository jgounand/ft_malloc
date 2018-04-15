/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 10:25:01 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/08 09:20:09 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*str;

	str = (char*)ft_memalloc(ft_strlen(src) + 1);
	if (!str)
		return (NULL);
	ft_strcpy(str, src);
	return (str);
}
