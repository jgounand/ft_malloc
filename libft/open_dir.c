/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:42:12 by jgounand          #+#    #+#             */
/*   Updated: 2018/04/15 11:50:16 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

DIR	*open_dir(char *path)
{
	DIR	*rep;

	if (!path)
		return (NULL);
	if (!(rep = opendir(path)))
		return (NULL);
	return (rep);
}
