/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quarter_scan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:57:21 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/23 17:25:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	next_scan(t_pos *dir, t_pos add, char **grid)
{
	while (dir->y < ft_strlen(grid[0]) && dir->x < 14 && dir->y > 0 && dir->x > 0 // w : 14 not modulable
		&& grid[(int)(dir->x)][(int)(dir->y)] == '0')
	{
		dir->y += add.y;
		dir->x += add.x;
	}
}

void	scan_ne(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;
	t_pos	add;
	t_pos	player;

	player = params->player.pos;
	add.x = -1;
	add.y = -1 / tan(M_PI / 2 - angle);
	horz.x = floor(player.x) - 0.01;
	horz.y = player.y - (player.x - floor(player.x)) / tan(M_PI / 2 - angle);
	next_scan(&horz, add, params->grid);
	add.y = 1;
	add.x = 1 * tan(M_PI / 2 - angle);
	vert.y = ceil(player.y);
	vert.x = player.x + (ceil(player.y) - player.y) * tan(M_PI / 2 - angle);
	next_scan(&vert, add, params->grid);
	params->scan.wall.y = (horz.y >= vert.y && horz.x <= vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.NO;
}

void	scan_sw(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;
	t_pos	add;
	t_pos	player;

	angle = angle - M_PI;
	player = params->player.pos;
	add.x = 1;
	add.y = 1 / tan(M_PI / 2 - angle);
	horz.x = ceil(player.x);
	horz.y = player.y - (player.x - ceil(player.x)) / tan(M_PI / 2 - angle);
	next_scan(&horz, add, params->grid);
	add.y = -1;
	add.x = -1 * tan(M_PI / 2 - angle);
	vert.y = floor(player.y) - 0.01;
	vert.x = player.x + (floor(player.y) - player.y) * tan(M_PI / 2 - angle);
	next_scan(&vert, add, params->grid);
		params->scan.wall.y = (horz.y < vert.y || horz.x > vert.x ? vert.y : horz.y);
		params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
		if (params->scan.wall.y == vert.y)
			params->scan.face = &params->graph.WE;
		else
			params->scan.face = &params->graph.SO;
}

void	scan_se(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;
	t_pos	add;
	t_pos	player;

	angle = angle + M_PI;
	player = params->player.pos;
	add.x = 1;
	add.y = 1 / tan(M_PI / 2 - angle);
	horz.x = ceil(player.x);
	horz.y = player.y - (player.x - ceil(player.x)) / tan(M_PI / 2 - angle);
	next_scan(&horz, add, params->grid);
	add.y = 1;
	add.x = 1 * tan(M_PI / 2 - angle);
	vert.y = ceil(player.y);
	vert.x = player.x + (ceil(player.y) - player.y) * tan(M_PI / 2 - angle);
	next_scan(&vert, add, params->grid);
	params->scan.wall.y = (horz.y > vert.y || horz.x > vert.x ? vert.y : horz.y);
	params->scan.wall.x = (params->scan.wall.y == vert.y ? vert.x : horz.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.EA;
	else
		params->scan.face = &params->graph.SO;
}

void	scan_nw(t_params *params, double angle)
{
	t_pos	horz;
	t_pos	vert;
	t_pos	add;
	t_pos	player;

	angle = angle - M_PI;
	player = params->player.pos;
	add.x = -1;
	add.y = -1 / tan(M_PI / 2 - angle);
	horz.x = floor(player.x) - 0.01;
	horz.y = player.y - (player.x - floor(player.x)) / tan(M_PI / 2 - angle);
	next_scan(&horz, add, params->grid);
	add.y = -1;
	add.x = -1 * tan(M_PI / 2 - angle);
	vert.y = floor(player.y) - 0.01;
	vert.x = player.x + (floor(player.y) - player.y) * tan(M_PI / 2 - angle);
	next_scan(&vert, add, params->grid);
	params->scan.wall.y = (horz.y >= vert.y  - 0.01 && horz.x >= vert.x  - 0.01? horz.y : vert.y);
	params->scan.wall.x = (params->scan.wall.y == horz.y ? horz.x : vert.x);
	if (params->scan.wall.y == vert.y)
		params->scan.face = &params->graph.WE;
	else
		params->scan.face = &params->graph.NO;
}
