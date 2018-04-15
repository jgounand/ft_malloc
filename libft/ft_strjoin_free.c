/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:21:36 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/02 18:02:46 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, short function)
{
	char	*tmp;

	tmp = NULL;
	if (s1 && !s2)
		tmp = ft_strdup(s1);
	else if (!s1 && s2)
		tmp = ft_strdup(s2);
	else if (s1 && s2)
	{
		tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (!tmp)
			return (NULL);
		ft_strcat(tmp, s1);
		ft_strcat(tmp, s2);
	}
	if (function == 0 || function == 2)
		ft_memdel((void **)&s1);
	else if (function == 1 || function == 2)
		ft_memdel((void **)&s2);
	return (tmp);
}
