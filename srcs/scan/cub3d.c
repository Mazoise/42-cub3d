/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:45:55 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 21:15:38 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

// int		draw_mini_map(t_params *params)
// {
// 	int			height;
// 	int			width;
// 	int			i;
// 	int			j;

// 	height = 0;
// 	width = 0;
// 	i = 0;
// 	j = 0;
// 	while (params->grid[i])
// 	{
// 		height = 0;
// 		j = 0;
// 		while (params->grid[i][j])
// 		{
// 			if (params->grid[i][j] == '1')
// 				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.NO.img, height, width);
// 			else if (params->grid[i][j] == '0')
// 				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.SO.img, height, width);
// 			else if (params->grid[i][j] == '2')
// 				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.EA.img, height, width);
// 			else
// 				mlx_put_image_to_window(params->ptr, params->wdw, params->graph.WE.img, height, width);
// 			j++;
// 			height += params->graph.EA.h;
// 		}
// 		width += params->graph.EA.w;
// 		i++;
// 	}
// 	mlx_put_image_to_window(params->ptr, params->wdw, params->graph.S.img, params->player.pos.y * params->graph.EA.h - 4, params->player.pos.x * params->graph.EA.h - 4);
// 	return (1);
// }

// int		mini_map(t_params *params)
// {
// 	int			height;
// 	int			width;
// 	int			i;
// 	int			j;

// 	height = params->max.j - params->max.j / 2;
// 	width = params->max.i - params->max.i / 2;
// 	i = 0;
// 	j = 0;

// 	if (!(params->minimap = mlx_new_image(params->ptr, width, height)))
// 		return (0);
// 	params->mini_m.img = mlx_get_data_addr(params->minimap, &params->mini_m.bpp, &params->mini_m.len, &params->mini_m.endian);
// 	while (i < height)
// 	{
// 		j = 0;
// 		while (j < width)
// 		{
// 			if (params->grid[(int)(i / height)][(int)(j / width)] == '1')
// 				int_to_img(&params->mini_m, 0xFFFFFF, i, j);
// 			else if (params->grid[(int)(i / height)][(int)(j / width)] == '0')
// 				int_to_img(&params->mini_m, 0xCCFFFFFF, i, j);
// 			else if (params->grid[(int)(i / height)][(int)(j / width)] == '2')
// 				int_to_img(&params->mini_m, 0x0000FF, i, j);
// 			else
// 				int_to_img(&params->mini_m, 0xFFFFFF, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// 	mlx_put_image_to_window(params->ptr, params->wdw, params->graph.S.img, params->player.pos.y * params->graph.EA.h - 4, params->player.pos.x * params->graph.EA.h - 4);
// 	return (1);
// }

int		main(int argc, char **argv)
{
	t_params	params;

	check_args(argc, argv, &params);
	if (!(params.ptr = mlx_init()))
	{
		ft_dprintf(2, "Error\nMlx error : %s (initialisation)\n", strerror(errno));
		return (0);
	}
	if (!(initialisation(argv[1], &params)))
		return (0);
	if (params.screenshot == 1)
		screenshot_bmp(&params);
	if (!(window_mlx(&params, "--- CUB 3D ---")))
		return(0);
	loop_mlx(&params);
}
