/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quarter_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:57:21 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/01 13:47:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void		next_scan(int *nb, t_pos *dir, t_pos add, char **grid)
{
	nb = 1;
	while (is_grid_pos(dir->x, dir->y, grid, '0')
		|| is_grid_pos(dir->x, dir->y, grid, '2'))
	{
		dir->y += add.y;
		dir->x += add.x;
		nb++; //unused
	}
}

void			scan_ne(t_params *params, double angle, t_pos *wall)
{
	t_pos	hrz;
	t_pos	vrt;
	t_pos	player;

	player = params->player.pos;
	params->scan.add_horz.x = -1;
	params->scan.add_horz.y = -1 / tan(M_PI_2 - angle);
	hrz.x = floor(player.x) - 0.01;
	hrz.y = player.y - (player.x - floor(player.x)) / tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.i, &hrz, params->scan.add_horz, params->grid);
	params->scan.add_vert.y = 1;
	params->scan.add_vert.x = 1 * tan(M_PI_2 - angle);
	vrt.y = ceil(player.y);
	vrt.x = player.x + (ceil(player.y) - player.y) * tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.j, &vrt, params->scan.add_vert, params->grid);
	wall->y = (hrz.y >= vrt.y && hrz.x <= vrt.x ? vrt.y : hrz.y);
	wall->x = (wall->y == vrt.y ? vrt.x : hrz.x);
	if (wall->y == vrt.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.NO;
}

void			scan_sw(t_params *params, double angle, t_pos *wall)
{
	t_pos	hrz;
	t_pos	vrt;
	t_pos	player;

	player = params->player.pos;
	params->scan.add_horz.x = 1;
	params->scan.add_horz.y = 1 / tan(M_PI_2 - angle);
	hrz.x = ceil(player.x);
	hrz.y = player.y - (player.x - ceil(player.x)) / tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.i, &hrz, params->scan.add_horz, params->grid);
	params->scan.add_vert.y = -1;
	params->scan.add_vert.x = -1 * tan(M_PI_2 - angle);
	vrt.y = floor(player.y) - 0.01;
	vrt.x = player.x + (floor(player.y) - player.y) * tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.j, &vrt, params->scan.add_vert, params->grid);
	wall->y = (hrz.y < vrt.y || hrz.x > vrt.x ? vrt.y : hrz.y);
	wall->x = (wall->y == vrt.y ? vrt.x : hrz.x);
	if (wall->y == vrt.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.SO;
}

void			scan_se(t_params *params, double angle, t_pos *wall)
{
	t_pos	hrz;
	t_pos	vrt;
	t_pos	player;

	player = params->player.pos;
	params->scan.add_horz.x = 1;
	params->scan.add_horz.y = 1 / tan(M_PI_2 - angle);
	hrz.x = ceil(player.x);
	hrz.y = player.y - (player.x - ceil(player.x)) / tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.i, &hrz, params->scan.add_horz, params->grid);
	params->scan.add_vert.y = 1;
	params->scan.add_vert.x = 1 * tan(M_PI_2 - angle);
	vrt.y = ceil(player.y);
	vrt.x = player.x + (ceil(player.y) - player.y) * tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.j, &vrt, params->scan.add_vert, params->grid);
	wall->y = (hrz.y > vrt.y || hrz.x > vrt.x ? vrt.y : hrz.y);
	wall->x = (wall->y == vrt.y ? vrt.x : hrz.x);
	if (wall->y == vrt.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.SO;
}

void			scan_nw(t_params *params, double angle, t_pos *wall)
{
	t_pos	hrz;
	t_pos	vrt;
	t_pos	player;

	player = params->player.pos;
	params->scan.add_horz.x = -1;
	params->scan.add_horz.y = -1 / tan(M_PI_2 - angle);
	hrz.x = floor(player.x) - 0.01;
	hrz.y = player.y - (player.x - floor(player.x)) / tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.i, &hrz, params->scan.add_horz, params->grid);
	params->scan.add_vert.y = -1;
	params->scan.add_vert.x = -1 * tan(M_PI_2 - angle);
	vrt.y = floor(player.y) - 0.01;
	vrt.x = player.x + (floor(player.y) - player.y) * tan(M_PI_2 - angle);
	next_scan(&params->scan.nb.j, &vrt, params->scan.add_vert, params->grid);
	wall->y = (hrz.y >= vrt.y - 0.01 && hrz.x >= vrt.x - 0.01 ? hrz.y : vrt.y);
	wall->x = (wall->y == hrz.y ? hrz.x : vrt.x);
	if (wall->y == vrt.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.NO;
}
