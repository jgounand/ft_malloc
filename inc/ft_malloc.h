/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgounand <joris@gounand.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 20:50:34 by jgounand          #+#    #+#             */
/*   Updated: 2019/09/10 13:00:22 by jgounand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <string.h>
# include <sys/mman.h>
# include "../libft/inc/libft.h"

# define TINY	512
# define SMALL	1024
# define NB_PAGES		1
# define MAX_TINY getpagesize() * NB_PAGES
# define MAX_MED getpagesize() * NB_PAGES
# define H_TINY (t_tny *)((void *)(g_mem + 1) + getpagesize() * S_HEADER_A)
# define H_MED (t_med *)((void *)(H_TINY) + getpagesize() * S_HEADER_T)
# define H_FAT (t_fat *)((void *)H_MED + getpagesize() * S_HEADER_M)
# define S_HEADER_T g_mem->nb_pages_header[0]
# define S_HEADER_M g_mem->nb_pages_header[1]
# define S_HEADER_F g_mem->nb_pages_header[2]
# define S_HEADER_A g_mem->nb_pages_header[3]
# define TINY_SIZE g_mem->max_size[0]
# define MED_SIZE g_mem->max_size[1]
# define FAT_SIZE g_mem->max_size[2]
# define A_SIZE g_mem->max_size[3]
# define MAX_HEADER(s,n) getpagesize() * (n) / sizeof(s)

/*
** Structure Tiny
** ptr => stock l'addresse
** size => positif = size memoire allouee
**		=> negatif = size memoire disponible
*/

typedef struct	s_tiny
{
	void		*ptr;
	int			size;
}				t_tny;

typedef t_tny	t_med;

/*
** Structure Fat
** ptr => stock l'addresse
** size => size memoire allouee
*/

typedef struct	s_fat
{
	void		*ptr;
	size_t		size;
}				t_fat;

/*
** Structure mem
** [0] => TINY, [1] => MED, [2] =>FAT, [3] => A (struct start)
** max_size => size_total / size of the struct
** nb_pages_header => nbr pages map for each struct
*/

typedef struct	s_mem
{
	size_t			max_size[4];
	unsigned int	nb_pages_header[4];
}				t_mem;

/*
** Struct start
** stock the start address mapped
*/

typedef struct	s_start
{
	void		*start;
	void		*start_tiny;
	void		*start_med;
}				t_start;

/*
**	Strucy infonode
**	left => nbr of node left
**	ptr_node => address of the struct
*/

typedef struct	s_infonode
{
	size_t		left;
	t_tny		*ptr_node;
}				t_infonode;

extern	t_mem	*g_mem;

/*
** ft_malloc.c
*/

void			*malloc(size_t size);
void			*add_small(short type, size_t lenght);
void			*add_node_free(t_tny *tmp, void *ptr, bool type);

/*
**	ft_realloc.c
*/

void			*realloc(void *ptr, size_t size);

/*
**	ft_free.c
*/

void			free(void *ptr);
t_fat			*get_fat(void *ptr);
t_tny			*ret_node(t_tny *tofree, void *ptr);

/*
**	mem.c
*/

void			*mem_data(short size);
void			add_mem_data(t_tny **tmp, short type, short position);
t_mem			*init_mem(void);
t_mem			*mem_header(unsigned int nb_pages[4]);

/*
**	mem_tools.c
*/

void			init_data_firsttime(void);

/*
**	add_mem_header.c
*/

bool			add_mem_header(short type);

/*
**	clear_node.c
*/

void			check_header_zero(short type);
t_tny			*get_free_node(short type, size_t lenght);
size_t			get_free_nodeleft(short type, size_t lenght);

/*
**	defragment.c
*/

void			try_defragment(t_tny *tofree);

/*
**	free_tools.c
*/

bool			not_begin_data(t_tny *tofree);
bool			diff_data(t_tny *tofree, bool type);
short			get_type(void *ptr);

/*
**	push_header.c
*/

size_t			push_header(t_tny **tmp, short type);
size_t			remove_header(t_tny **tmp, size_t bytes_cpy, short type);

/*
**	print_addrhex.c
*/

void			print_addrhex(int p);

/*
**	realloc_node.c
*/
void			*r_with_node(t_tny **node, size_t size, short type);
void			*r_with_node1(t_tny **node, size_t size, short type);
void			*r_mall_free(t_tny *node, size_t size);

/*
**	show_alloc_mem.c
*/

void			show_alloc_mem(void);

/*
**	tools.c
*/

void			add_rm_header(short add, short type);
short			check_header_left(void);
t_start			*get_start(void *ptr, bool next);
t_start			*get_new_data(void *ptr, bool type);

/*
**	tools2.c
*/

void			*get_addr(void *ptr);

/*
**	show_alloc_mem_tools.c
*/

size_t			print_lignes_tymed(short type, t_tny *node, bool all);
size_t			print_lignes_fat(t_fat *node, bool all);
size_t			print_lignes_headers(void);

#endif
