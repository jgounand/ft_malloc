/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 08:32:36 by jgounand          #+#    #+#             */
/*   Updated: 2018/01/09 20:42:53 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbr_word(char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			word++;
		while (str[i] != c && str[i])
			i++;
	}
	return (word);
}

static int		ft_car_word(char *str, int position, char c)
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
		while (str[i] == c)
			i++;
		if (str[i] != '\0')
			word++;
		while (str[i] != c && str[i])
		{
			cpt++;
			i++;
		}
	}
	return (cpt);
}

static void		ft_copie(char **dest, char *src, int word, char c)
{
	unsigned int	index;
	int				j;
	int				car;

	car = 0;
	j = 0;
	index = 0;
	while (j < word)
	{
		while (src[index] == c)
			index++;
		while (src[index] != c && src[index])
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

char			**ft_strsplit(char const *s, char c)
{
	char	*str1;
	char	**str2;
	int		word;
	int		i;

	str1 = (char *)s;
	if (!s)
		return (NULL);
	if (!(word = ft_nbr_word(str1, c)))
		return (NULL);
	str2 = (char**)ft_memalloc(sizeof(char*) * (word + 1));
	if (!str2)
		return (NULL);
	i = -1;
	while (++i < word)
	{
		str2[i] = (char *)ft_memalloc(sizeof(char **) *
				ft_car_word(str1, i, c) + 1);
		if (!str2[i])
			return (NULL);
	}
	ft_copie(str2, str1, word, c);
	return (str2);
}
