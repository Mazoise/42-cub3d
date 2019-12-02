/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 21:15:21 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/02 11:40:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void		which_add(t_pos *add, double angle, int idx)
{
	if (idx == 1)
	{
		add->x = -1;
		add->y = -1 / tan(M_PI_2 - angle);
	}
	else if (idx == 2)
	{
		add->x = 1;
		add->y = 1 / tan(M_PI_2 - angle);
	}
	else if (idx == 3)
	{
		add->y = 1;
		add->x = 1 * tan(M_PI_2 - angle);
	}
	else
	{
		add->y = -1;
		add->x = -1 * tan(M_PI_2 - angle);
	}
}

void		which_start(t_pos *scan, t_pos pos, double angle, int idx)
{
	if (idx == 1)
	{
		scan->x = floor(pos.x) - 0.00001;
		scan->y = pos.y - (pos.x - floor(pos.x)) / tan(M_PI_2 - angle);
	}
	else if (idx == 2)
	{
		scan->x = ceil(pos.x);
		scan->y = pos.y - (pos.x - ceil(pos.x)) / tan(M_PI_2 - angle);
	}
	else if (idx == 3)
	{
		scan->y = ceil(pos.y);
		scan->x = pos.x + (ceil(pos.y) - pos.y) * tan(M_PI_2 - angle);
	}
	else
	{
		scan->y = floor(pos.y) - 0.00001;
		scan->x = pos.x + (floor(pos.y) - pos.y) * tan(M_PI_2 - angle);
	}
}

int			close_cam(t_scan *scan, t_pos cam, int *nb, char **grid)
{
	if (sqrt(pow(cam.x - scan->vrt.x, 2) + pow(cam.y - scan->vrt.y, 2))
		>= sqrt(pow(cam.x - scan->hrz.x, 2) + pow(cam.y - scan->hrz.y, 2)))
	{
		scan->wall.x = scan->hrz.x;
		scan->wall.y = scan->hrz.y;
		if (!(is_grid_pos(scan->wall.x, scan->wall.y, grid, '0'))
			&& !(is_grid_pos(scan->wall.x, scan->wall.y, grid, '2')))
			return (0);
		scan->hrz.x += scan->add_horz.x;
		scan->hrz.y += scan->add_horz.y;
	}
	else
	{
		scan->wall.x = scan->vrt.x;
		scan->wall.y = scan->vrt.y;
		if (!(is_grid_pos(scan->wall.x, scan->wall.y, grid, '0'))
			&& !(is_grid_pos(scan->wall.x, scan->wall.y, grid, '2')))
			return (0);
		scan->vrt.x += scan->add_vert.x;
		scan->vrt.y += scan->add_vert.y;
	}
	(*nb)++;
	return(1);
}
