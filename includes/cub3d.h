/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 11:01:01 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/08 22:15:38 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/errno.h>
# define FULLSCREEN_H 1400
# define FULLSCREEN_W 2560
# define CAM_L 0
# define CAM_R 1
# define FORW 2
# define BCKW 3
# define LEFT 4
# define RGHT 5
# define MAP 6
# define OBJ 7
# define EVENTS 8
# define BONUS 1

typedef union u_squ
{
		float f;
		uint32_t i;
}			 t_squ;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_idx
{
	int				i;
	int				j;
}					t_idx;
typedef struct		s_mlx_img
{
	char			*img;
	int				endian;
	int				bpp;
	int				len;
}					t_mlx_img;

typedef struct		s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				true;
}					t_rgb;

typedef struct		s_colors
{
	t_rgb			zero;
	t_rgb			one;
	t_rgb			two;
	t_rgb			out;
	t_rgb			player;
}					t_colors;

typedef struct		s_texture
{
	int				h;
	int				w;
	void			*img;
	t_mlx_img		txtr;
}					t_texture;

typedef struct		s_graph
{
	t_texture		NO;
	t_texture		SO;
	t_texture		WE;
	t_texture		EA;
	t_texture		S;
	t_rgb			F;
	t_rgb			C;
}					t_graph;

 typedef struct 		s_scan
{
	t_pos			wall;
	t_texture		*face;
	t_pos			vrt;
	t_pos			hrz;
	t_pos			add_vert;
	t_pos			add_horz;
	int 			nb;
}					t_scan;

typedef struct		s_player
{
	t_pos			pos;
	double			compas;
}					t_player;
typedef struct 		s_calc
{
	double			proj;
	double			step;
	double			turn;
}					t_calc;

typedef struct		s_bonus
{
	t_texture		F;
	t_texture		C;
	t_colors		colors;
	t_idx			idx;
}					t_bonus;
typedef struct		s_params
{
	void			*ptr;
	void			*wdw;
	void			*fullscreen;
	void			*minimap;
	t_idx			max;
	char			**grid;
	t_graph			graph;
	t_player		player;
	t_scan			scan;
	t_mlx_img		img;
	t_mlx_img		mini_m;
	char			event[EVENTS];
	t_calc			calc;
	int				screenshot;
	t_bonus			bonus;
}					t_params;

int			initialisation(char *mapcub, t_params *params);
int			read_map(char *mapcub, t_params *params);
int			init_player(t_player *player, char **grid);
void		init_struct(t_params *params);
int			check_all_params(t_params *params);
void		check_format(char *str);
int			is_compas(char c);
int			is_grid(char c);
int			conv_texture(char *str, t_params *params, char c);
int			conv_color(char *str, t_params *params, char c);
int			conv_resolution(char *str, t_params *params);
int			conv_grid(char *str, t_params *params);
void		line_put(t_params *params, double inc, int i, double angle);
void		img_to_intne(t_mlx_img tmp, t_texture *txtr);
void		img_to_intsw(t_mlx_img tmp, t_texture *txtr);
void		rgb_to_img(t_mlx_img *img, t_rgb color, int i, int j);
int			is_grid_pos(double x, double y, char **grid, char c);
void		correct_compas(double *compas);
int			init_mlx(t_params *params, char *name);
void		key_events(t_params *params);
int			press_key(int keycode, t_params *params);
int			release_key(int keycode, t_params *params);
int			exit_wdw(t_params *params);
int			window_mlx(t_params *params, char *name);
void		loop_mlx(t_params *params);
int			draw_in_wdw(t_params *params);
void		full_scan(t_params *params);
int			draw_mini_map(t_params *params);
void		screenshot_bmp(t_params *params);
void		check_args(int argc, char **argv, t_params *params);
void		pre_calc(t_params *params);
void		free_all(t_params *params);
void		sprite(t_params *params, double angle, int i);
void		texture_put(t_params *params, double height, double pct, t_idx *idx);
void		which_start(t_pos *scan, t_pos pos, double angle, int idx);
void		which_add(t_pos *add, double angle, int idx);
int			close_cam(t_scan *scan, t_pos cam, int *nb, char **grid);
void		put_pix(t_mlx_img *img, t_mlx_img txtr, int dst, int src);
void		cf_put(t_params *params, t_idx *idx, double height, double angle);
double		rsqrt(double number);
void		player_error(int pos);
void		txtr_error(char c);
int			create_image(t_params *params, void *img, t_mlx_img *im, t_idx idx);
int			draw_mini_map(t_params *params);

#endif
