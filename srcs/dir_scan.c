/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_scan.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 18:21:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/21 19:19:30 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_pos	floor_scan_horz(t_pos *player, char **grid, double angle)
{
	t_pos	add;
	t_pos	dir;

	add.x = -1;
	add.y = -1 / tan(M_PI / 2 - angle);
	dir.x = floor(player->x) - 0.01;
	dir.y = player->y - (player->x - floor(player->x)) / tan(M_PI / 2 - angle);
	while (dir.y < ft_strlen(grid[0]) && dir.x < 14 && dir.y > 0 && dir.x > 0 // w : 14 not modulable
		&& grid[(int)(dir.x)][(int)(dir.y)] == '0')
	{
		dir.y += add.y;
		dir.x += add.x;
	}
	return (dir);
}

t_pos	floor_scan_vert(t_pos *player, char **grid, double angle)
{
	t_pos	add;
	t_pos	dir;

	add.y = -1;
	add.x = -1 * tan(M_PI / 2 - angle);
	dir.y = floor(player->y) - 0.01;
	dir.x = player->x + (floor(player->y) - player->y) * tan(M_PI / 2 - angle);
	while (dir.y < ft_strlen(grid[0]) && dir.x < 14 && dir.y > 0 && dir.x > 0 // w : 14 not modulable
		&& grid[(int)(dir.x)][(int)(dir.y)] == '0')
	{
		dir.y += add.y;
		dir.x += add.x;
	}
	return (dir);
}

t_pos	ceil_scan_horz(t_pos *player, char **grid, double angle)
{
	t_pos	add;
	t_pos	dir;

	add.x = 1;
	add.y = 1 / tan(M_PI / 2 - angle);
	dir.x = ceil(player->x);
	dir.y = player->y - (player->x - ceil(player->x)) / tan(M_PI / 2 - angle);
	while (dir.y < ft_strlen(grid[0]) && dir.x < 14 && dir.y > 0 && dir.x > 0 // w : 14 not modulable
		&& grid[(int)(dir.x)][(int)(dir.y)] == '0')
	{
		dir.y += add.y;
		dir.x += add.x;
	}
	return (dir);
}

t_pos	ceil_scan_vert(t_pos *player, char **grid, double angle)
{
	t_pos	add;
	t_pos	dir;

	add.y = 1;
	add.x = 1 * tan(M_PI / 2 - angle);
	dir.y = ceil(player->y);
	dir.x = player->x + (ceil(player->y) - player->y) * tan(M_PI / 2 - angle);
	while (dir.y < ft_strlen(grid[0]) && dir.x < 14 && dir.y > 0 && dir.x > 0 // w : 14 not modulable
		&& grid[(int)(dir.x)][(int)(dir.y)] == '0')
	{
		dir.y += add.y;
		dir.x += add.x;
	}
	return (dir);
}
