/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/20 13:36:19 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

int		press_key(int keycode, void *param)
{
	t_params	*params;
	double		x_dir;
	double		y_dir;

	x_dir = 0;
	y_dir = 0;

	params = param;
	if (keycode == 13)
		x_dir -= 0.1;
	if (keycode == 1)
		x_dir += 0.1;
	if (keycode == 0)
		y_dir -= 0.1;
	if (keycode == 2)
		y_dir += 0.1;
	if (x_dir + params->player.pos.x > 0.5 && x_dir + params->player.pos.x < params->max.x - 0.5
		&& y_dir + params->player.pos.y > 0.5 && y_dir + params->player.pos.y < params->max.y - 0.5
		&& params->grid[(int)(x_dir + params->player.pos.x)][(int)(y_dir + params->player.pos.y)] == '0')
	{
		params->player.pos.x += x_dir;
		params->player.pos.y += y_dir;
		return (1);
	}
	return (0);
}

int		ft_exit(int	i)
{
	exit(i);
	return (0);
}

// int		draw(void *param)
// {
// 	t_params	*params;
// 	double		y_check;
// 	double		x_check;
// 	int			i;
// 	double		angle;

// 	angle = -0.3;
// 	i = 0;
// 	while (angle <= 0.3)
// 	{
// 		if (params->player.bousole = 'N')
// 			y_check = rounded_down(params->player.pos.y/64) * (64) - 1;
// 		else
// 			y_check = rounded_down(params->player.pos.y/64) * (64) + 64;

// 		x_check = params->player.pos.x + (params->player.pos.y-y_check)/tan(angle);
// 	}
// }

int		draw_mini_map(void *param)
{
	t_params	*params;
	int			height;
	int			width;
	int			i;
	int			j;

	height = 0;
	width = 0;
	i = 0;
	j = 0;
	params = (t_params*)param;
	while (params->grid[i])
	{
		height = 0;
		j = 0;
		while (params->grid[i][j])
		{
			if (params->grid[i][j] == '1')
				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.NO.img, height, width);
			else if (params->grid[i][j] == '0')
				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.WE.img, height, width);
			else if (params->grid[i][j] == '2')
				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.EA.img, height, width);
			else
				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.SO.img, height, width);
			j++;
			height += params->graph.EA.h;
		}
		width += params->graph.EA.w;
		i++;
	}
	mlx_put_image_to_window(params->ptr, params->wdw, params->graph.S.img, params->player.pos.y * params->graph.EA.h - 3, params->player.pos.x * params->graph.EA.h - 3);
	return (1);
}

int		stop(int keycode, void *param)
{
	t_params	*params;

	params = (t_params*)param;
	if (keycode == 53)
	{
		mlx_destroy_window(params->ptr, params->wdw);
		exit(0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_params	params;

	if (argc <= 1)
	{
		ft_printf("Error\nMissing file format\n");
		return (0);
	}
	if (!(params.ptr = mlx_init()))
	{
		ft_printf("Error\nMLX1 error\n");
		return (0);
	}
	if (!(initialisation(argv[1], &params)))
	{
		ft_printf("Init error\n");
		return (0);
	}
	if (!(params.wdw = mlx_new_window(params.ptr, params.max.x, params.max.y, "This is the window")))
	{
		ft_printf("ERROR WINDOW\n"); //w
		return (0);
	}
	mlx_hook(params.wdw, 17, 0, ft_exit, 0);
	mlx_key_hook(params.wdw, stop, &params);
//	mlx_hook (params.wdw, 3, 1L << 1, release_key, &params);
	mlx_loop_hook(params.ptr, draw_mini_map, &params);
	mlx_hook (params.wdw, 2, 1L << 0, press_key, &params);
	mlx_loop(params.ptr);
}
