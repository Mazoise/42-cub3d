/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/21 17:44:13 by mchardin         ###   ########.fr       */
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
	if (keycode == 12)
		params->player.compas -= M_PI/12;
	else if (keycode == 14)
		params->player.compas += M_PI/12;
	if (params->player.compas >= 2 * M_PI)
		params->player.compas = params->player.compas - 2 * M_PI;
	else if (params->player.compas < 0)
		params->player.compas = params->player.compas + 2 * M_PI;
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
	}
	else
		return (0);
	return (1);
}

int		ft_exit(int	i)
{
	exit(i);
	return (0);
}

// int		draw(void *param)
// {

// 	return (1);
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
	mlx_put_image_to_window(params->ptr, params->wdw, params->graph.S.img, params->player.pos.y * params->graph.EA.h - 4, params->player.pos.x * params->graph.EA.h - 4);
	
	double		y_check_h;
	double		x_check_h;
	double		y_check_v;
	double		x_check_v;
	double		y_add;
	double		x_add;
	double		y_wall;
	double		x_wall;
	double		angle;
	// int		end;

	angle = params->player.compas - M_PI / 6;
	if (angle < 0)
		angle = 2 * M_PI + angle;
	ft_printf("Angle : %d\n", (int)(angle * (180 / M_PI)));
	if (angle >= M_PI / 2 && angle < M_PI)
	{
		x_add = -1;
		y_add = -1 / tan(M_PI / 2 - angle);
		x_check_h = floor(params->player.pos.x) - 0.01;
		y_check_h = params->player.pos.y - (params->player.pos.x - floor(params->player.pos.x)) / tan(M_PI / 2 - angle);
		if (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		while (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0 && params->grid[(int)(x_check_h)][(int)(y_check_h)] == '0')
		{
			y_check_h += y_add;
			x_check_h += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		}
		y_add = 1;
		x_add = 1 * tan(M_PI / 2 - angle);
		y_check_v = ceil(params->player.pos.y);
		x_check_v = params->player.pos.x + (ceil(params->player.pos.y) - params->player.pos.y) * tan(M_PI / 2 - angle);
		if (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		while (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0 && params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
		{
			y_check_v += y_add;
			x_check_v += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		}
		y_wall = (y_check_h > y_check_v || x_check_h < x_check_v ? y_check_v : y_check_h);
		x_wall = (y_wall == y_check_v ? x_check_v : x_check_h);
		mlx_pixel_put(params->ptr, params->wdw, y_wall * params->graph.EA.h, x_wall * params->graph.EA.h, 0xff0000);
	}
	else if (angle > (3 * M_PI) / 2)
	{
		x_add = 1;
		y_add = 1 / tan(M_PI / 2 - angle);
		x_check_h = ceil(params->player.pos.x);
		y_check_h = params->player.pos.y - (params->player.pos.x - ceil(params->player.pos.x)) / tan(M_PI / 2 - angle);
		if (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		while (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0 && params->grid[(int)(x_check_h)][(int)(y_check_h)] == '0')
		{
			y_check_h += y_add;
			x_check_h += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		}
		y_add = -1;
		x_add = -1 * tan(M_PI / 2 - angle);
		y_check_v = floor(params->player.pos.y) - 0.01;
		x_check_v = params->player.pos.x + (floor(params->player.pos.y) - params->player.pos.y) * tan(M_PI / 2 - angle);
		if (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		while (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0 && params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
		{
			y_check_v += y_add;
			x_check_v += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		}
		y_wall = (y_check_h < y_check_v || x_check_h > x_check_v ? y_check_v : y_check_h);
		x_wall = (y_wall == y_check_v ? x_check_v : x_check_h);
		mlx_pixel_put(params->ptr, params->wdw, y_wall * params->graph.EA.h, x_wall * params->graph.EA.h, 0xff0000);
	}
	else if (angle < M_PI / 2)
	{
		x_add = 1;
		y_add = 1 / tan(M_PI / 2 - angle);
		x_check_h = ceil(params->player.pos.x);
		y_check_h = params->player.pos.y - (params->player.pos.x - ceil(params->player.pos.x)) / tan(M_PI / 2 - angle);
		if (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		while (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0 && params->grid[(int)(x_check_h)][(int)(y_check_h)] == '0')
		{
			y_check_h += y_add;
			x_check_h += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		}
		y_add = 1;
		x_add = 1 * tan(M_PI / 2 - angle);
		y_check_v = ceil(params->player.pos.y);
		x_check_v = params->player.pos.x + (ceil(params->player.pos.y) - params->player.pos.y) * tan(M_PI / 2 - angle);
		if (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		while (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0 && params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
		{
			y_check_v += y_add;
			x_check_v += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		}
		y_wall = (y_check_h > y_check_v || x_check_h > x_check_v ? y_check_v : y_check_h);
		x_wall = (y_wall == y_check_v ? x_check_v : x_check_h);
		mlx_pixel_put(params->ptr, params->wdw, y_wall * params->graph.EA.h, x_wall * params->graph.EA.h, 0xff0000);
	}
	else
	{
		x_add = -1;
		y_add = -1 / tan(M_PI / 2 - angle);
		x_check_h = floor(params->player.pos.x) - 0.01;
		y_check_h = params->player.pos.y - (params->player.pos.x - floor(params->player.pos.x)) / tan(M_PI / 2 - angle);
		if (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		while (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14 && y_check_h > 0 && x_check_h > 0 && params->grid[(int)(x_check_h)][(int)(y_check_h)] == '0')
		{
			y_check_h += y_add;
			x_check_h += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x00ff00);
		}
		y_add = -1;
		x_add = -1 * tan(M_PI / 2 - angle);
		y_check_v = floor(params->player.pos.y) - 0.01;
		x_check_v = params->player.pos.x + (floor(params->player.pos.y) - params->player.pos.y) * tan(M_PI / 2 - angle);
		if (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0)
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		while (y_check_v < ft_strlen(params->grid[0]) && x_check_v < 14 && y_check_v > 0 && x_check_v > 0 && params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
		{
			y_check_v += y_add;
			x_check_v += x_add;
			mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0xffffff);
		}
		y_wall = (y_check_h < y_check_v || x_check_h < x_check_v ? y_check_v : y_check_h);
		x_wall = (y_wall == y_check_v ? x_check_v : x_check_h);
		mlx_pixel_put(params->ptr, params->wdw, y_wall * params->graph.EA.h, x_wall * params->graph.EA.h, 0xff0000);
	}
	
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


// angle = 90 - params->player.compas - 30;
// 	if (90 - params->player.compas + 30 > 360)
// 		end = 90 - params->player.compas + 30 - 360;
// 	else
// 		end = 90 - params->player.compas + 30;
// 	while (angle != end)
// 	{
// 		x_check_h = floor(params->player.pos.x);
// 			x_add = 1;
// 		y_check_h = params->player.pos.y + (params->player.pos.x-x_check_h)/tan(angle);
// 		y_add = 1/tan(angle);
// 		mlx_pixel_put(params->ptr, params->wdw, y_check_h * params->graph.EA.h, x_check_h * params->graph.EA.h, 0x0000ff);
// 		if (angle >= 720 && angle <= 90)
// 		{
// 			y_check_v = floor(params->player.pos.y) - 0.001;
// 			y_add = 1;
// 		}
// 		else
// 		{
// 			y_check_v = floor(params->player.pos.y);
// 			y_add = -1;
// 		}
// 		x_check_v = params->player.pos.x + (params->player.pos.y-y_check_v)/tan(angle);
// 		x_add = 1/tan(angle);
// 		// while (params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
// 		// {
// 		// 	y_check_v += y_add;
// 		// 	x_check_v += x_add;
// 		// }
// 		mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0x00ff00);
// 		angle++;
// 		if (angle >= 360)
// 			angle = angle - 360;
// 	}



// y_add = -1;
// 	x_add = -1 / tan(90 - angle);
// 	y_check_v = floor(params->player.pos.y) - 0.01;
// 	x_check_v = params->player.pos.x + ((floor(params->player.pos.y) - params->player.pos.y) / tan(90 - angle));
// //	if (y_check_h < ft_strlen(params->grid[0]) && x_check_h < 14)
// 		mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0x00ff00);
// 	while (params->grid[(int)(x_check_v)][(int)(y_check_v)] == '0')
// 	{
// 		y_check_v += y_add;
// 		x_check_v += x_add;
// 		mlx_pixel_put(params->ptr, params->wdw, y_check_v * params->graph.EA.h, x_check_v * params->graph.EA.h, 0x00ff00);
// 	}