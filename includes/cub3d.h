/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:01:01 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/24 19:44:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <OpenGL/gl3.h>
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <math.h>
# define CAM_L 0
# define CAM_R 1
# define FORW 2
# define BCKW 3
# define LEFT 4
# define RGHT 5
# define MAP 6

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_texture
{
	int				h;
	int				w;
	void			*img;
	unsigned int	*txtr;
}					t_texture;

typedef struct		s_mlx_img
{
	char			*img;
	int				endian;
	int				bpp;
	int				len;
}					t_mlx_img;

typedef struct		s_graph
{
	t_texture		NO;
	t_texture		SO;
	t_texture		WE;
	t_texture		EA;
	t_texture		S;
	unsigned int				F;
	unsigned int				C;
}					t_graph;

typedef struct 		s_scan
{
	t_pos			wall;
	t_pos 			sprite;
	t_texture		*face;
}					t_scan;

typedef struct		s_player
{
	t_pos			pos;
	double			compas;
}					t_player;

typedef struct		s_params
{
	void			*ptr;
	void			*wdw;
	void			*fullscreen;
	t_pos			max;
	char			**grid;
	t_graph			graph;
	t_player		player;
	t_scan			scan;
	t_mlx_img		img;
	char			event[7];
}					t_params;

typedef struct		s_RGB
{
	unsigned char	Red;
	unsigned char	Green;
	unsigned char	Blue;
}					t_RGB;

void		init_struct(t_params *params);
int			check_format(char *str);
int			is_valid_grid_element(char c);
int			is_save_request(char *str);
int			get_texture(char *path, t_texture *txtr, void *ptr, char c);
int			conv_texture(char *str, t_params *params, char c);
void		ft_RGB_to_int(t_params *params, t_RGB color, char c);
int			conv_color(char *str, t_params *params, char c);
int			conv_resolution(char *str, t_params *params);
int			fill_grid(char *str, t_params *params);
int			first_fill_grid(char *str, t_params *params);
int			check_all_params(t_params *params);
int			conv_grid(char *str, t_params *params);
int			conv_params(char *str, t_params *params);
int			convert_line(char *str, t_params *params);
int			read_map(char *mapcub, t_params *params);
int			initialisation(char *mapcub, t_params *params);
int			convert_read(int fd, t_params *params);
int			init_player(t_params *params);
int			check_n_pos(t_player *player, char **grid);
int			closed_grid(char **grid);
void		scan_ne(t_params *params, double angle);
void		scan_sw(t_params *params, double angle);
void		scan_se(t_params *params, double angle);
void		scan_nw(t_params *params, double angle);
void		line_put(t_params *params, double inc, int i);
void		img_to_intNE(t_mlx_img tmp, t_texture *txtr);
void		img_to_intSW(t_mlx_img tmp, t_texture *txtr);

#endif