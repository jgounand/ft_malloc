/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 13:29:13 by jgounand          #+#    #+#             */
/*   Updated: 2018/05/24 14:36:05 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		find_the_line(t_gnl *gnl, char **line, int i)
{
	char	*ptr;

	ptr = NULL;
	while (1)
	{
		if (gnl->size == 0 &&
				(((gnl->size = read(gnl->fd, gnl->buff, BUFF_SIZE)) == 0)
				|| gnl->size < 0))
			return (*line ? 1 : gnl->size);
		ptr = ft_memchr(gnl->buff, '\n', gnl->size);
		gnl->size = !ptr ? gnl->size : gnl->size - (ptr - gnl->buff) - 1;
		if (!(*line = ft_realloc_p(*line, i, !ptr ? gnl->size + i + 1 :
						(ptr - gnl->buff) + 1 + i)))
			return (-1);
		ft_memmove((*line) + i, gnl->buff, !ptr ? gnl->size : ptr - gnl->buff);
		if (ptr == NULL && ((i += gnl->size) || !(i += gnl->size)))
			gnl->size = 0;
		else
			return (ft_memmove(gnl->buff, gnl->buff + (++ptr - gnl->buff),
						gnl->size) ? 1 : 1);
	}
	return (0);
}

void	freeall(t_list *list)
{
	t_gnl	*gnl;

	if (!list)
		;
	gnl = (t_gnl *)(list->content);
	ft_memdel((void **)&gnl->buff);
	ft_memdel((void **)&gnl);
	ft_memdel((void **)&list);
}

t_gnl	*gen_gnl(int const fd, t_list **list)
{
	t_list	*tmp;
	t_gnl	*gnl;

	tmp = *list;
	while (tmp)
	{
		gnl = (t_gnl *)(tmp->content);
		if (gnl->fd == fd)
			return (gnl);
		tmp = tmp->next;
	}
	if ((gnl = (t_gnl *)ft_memalloc(sizeof(t_gnl))) == NULL)
		return (NULL);
	if ((gnl->buff = (char *)ft_memalloc(BUFF_SIZE + 1)) == NULL)
		return (NULL);
	gnl->size = 0;
	gnl->fd = fd;
	if (!(tmp = ft_lstnew(gnl, sizeof(t_gnl))))
		return (NULL);
	*list = tmp;
	gnl->fd = fd;
	free(gnl);
	return (tmp->content);
}

int		get_next_line(int const fd, char **line)
{
	static	t_list	*lst;
	t_gnl			*gnl;
	int				ret;

	if (!BUFF_SIZE)
		return (-1);
	if (fd == -2 && line)
		freeall(lst);
	if (fd < 0 || line == NULL)
		return (-1);
	if (!(gnl = gen_gnl(fd, &lst)))
		return (-1);
	*line = NULL;
	ret = 0;
	if ((ret = find_the_line(gnl, line, ret)) == 1 || ret == -1)
		return (ret == 1 ? 1 : -1);
	freeall(lst);
	return (0);
}
