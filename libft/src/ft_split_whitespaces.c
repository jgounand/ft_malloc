/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:40:08 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/09 20:41:36 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
			c == ' ')
		return (1);
	else
		return (0);
}

static int		ft_nbr_word(char *str)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\0')
			word++;
		while (!ft_isspace(str[i]) && str[i])
			i++;
	}
	return (word);
}

static int		ft_car_word(char *str, int position)
{
	int	i;
	int	cpt;
	int	word;

	i = 0;
	cpt = 0;
	word = 0;
	while (word != position + 1)
	{
		cpt = 0;
		while (ft_isspace(str[i]))
			i++;
		if (str[i] != '\0')
			word++;
		while (!ft_isspace(str[i]) && str[i])
		{
			cpt++;
			i++;
		}
	}
	return (cpt);
}

static void		ft_copie(char **dest, char *src, int word)
{
	unsigned int	index;
	int				j;
	int				car;

	car = 0;
	j = 0;
	index = 0;
	while (j < word)
	{
		while (ft_isspace(src[index]))
			index++;
		while (!ft_isspace(src[index]) && src[index])
		{
			dest[j][car] = src[index];
			index++;
			car++;
		}
		dest[j][car] = '\0';
		car = 0;
		j++;
	}
}

char			**ft_split_whitespaces(char const *s)
{
	char	*str1;
	char	**str2;
	int		word;
	int		i;

	str1 = (char *)s;
	if (!s)
		return (NULL);
	if (!(word = ft_nbr_word(str1)))
		return (NULL);
	str2 = (char**)ft_memalloc(sizeof(char*) * (word + 1));
	if (!str2)
		return (NULL);
	i = -1;
	while (++i < word)
	{
		str2[i] = (char *)ft_memalloc(sizeof(char **) *
				ft_car_word(str1, i) + 1);
		if (!str2[i])
			return (NULL);
	}
	ft_copie(str2, str1, word);
	return (str2);
}
