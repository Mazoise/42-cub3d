/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/19 20:23:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit(int	i)
{
	exit(i);
	return (0);
}

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
			if (i == params->player.pos.x && j == params->player.pos.y)
				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.S.img, height, width);
			else if (params->grid[i][j] == '1')
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
	mlx_loop_hook(params.ptr, draw_mini_map, &params);
	mlx_loop(params.ptr);
}
