/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:49:07 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/27 15:11:28 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		dir_vect(t_pos *dir, double compas)
{
	correct_compas(&compas);
	dir->y += 0.1 * sin(compas);
	dir->x += 0.1 * cos(compas);
}

void		walk_here(t_pos dir, t_pos *pos, char **grid)
{
	if (is_grid_pos(dir.x, dir.y, grid, '0'))
	{
		pos->x = dir.x;
		pos->y = dir.y;
	}
	else if (is_grid_pos(dir.x, pos->y, grid, '0'))
		pos->x = dir.x;
	else if (is_grid_pos(pos->x, dir.y, grid, '0'))
		pos->y = dir.y;
}

void		key_events(t_params *params)
{
	t_pos		dir;

	dir.x = params->player.pos.x;
	dir.y = params->player.pos.y;

	if (params->event[CAM_L] == 1)
		params->player.compas += M_PI/36;
	if (params->event[CAM_R] == 1)
		params->player.compas -= M_PI/36;
	correct_compas(&params->player.compas);
	if (params->event[FORW] == 1)
		dir_vect(&dir, params->player.compas);
	if (params->event[BCKW] == 1)
		dir_vect(&dir, params->player.compas + M_PI);
	if (params->event[LEFT] == 1)
		dir_vect(&dir, params->player.compas + M_PI / 2);
	if (params->event[RGHT] == 1)
		dir_vect(&dir, params->player.compas + (3 * M_PI) / 2);
	walk_here(dir, &params->player.pos, params->grid);
	if (params->event[MAP] == 1)
		draw_mini_map(params);
}

int			press_key(int keycode, t_params *params)
{
	ft_printf("Keycode pressed: %d\n", keycode);
	if (keycode == 14 || keycode == 124)
		params->event[CAM_R] = 1;
	else if (keycode == 12 || keycode == 123)
		params->event[CAM_L] = 1;
	else if (keycode == 48)
		params->event[MAP] = 1;
	else if (keycode == 13)
		params->event[FORW] = 1;
	else if (keycode == 1)
		params->event[BCKW] = 1;
	else if (keycode == 0)
		params->event[LEFT] = 1;
	else if (keycode == 2)
		params->event[RGHT] = 1;
	return (1);
}

int		release_key(int keycode, t_params *params)
{
	ft_printf("Keycode released: %d\n", keycode);
	if (keycode == 53)
		exit_wdw(params);
	else if (keycode == 14 || keycode == 124)
		params->event[CAM_R] = 0;
	else if (keycode == 12 || keycode == 123)
		params->event[CAM_L] = 0;
	else if (keycode == 48)
		params->event[MAP] = 0;
	else if (keycode == 13)
		params->event[FORW] = 0;
	else if (keycode == 1)
		params->event[BCKW] = 0;
	else if (keycode == 0)
		params->event[LEFT] = 0;
	else if (keycode == 2)
		params->event[RGHT] = 0;
	return (1);
}
