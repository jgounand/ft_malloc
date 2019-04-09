/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:33:04 by jgounand          #+#    #+#             */
/*   Updated: 2017/11/08 13:56:28 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	int	cpt_end;
	int	len;
	int cpt_start;

	if (!s)
		return (NULL);
	cpt_end = 0;
	cpt_start = 0;
	len = ft_strlen(s);
	while (ft_iswhitespace(s[cpt_start]))
		cpt_start++;
	while (ft_iswhitespace(s[len - 1 - cpt_end]))
		cpt_end++;
	if ((len - cpt_start - cpt_end) <= 0)
		return (ft_strnew(0));
	return (ft_strsub(s, cpt_start, (size_t)(len - cpt_start - cpt_end)));
}
