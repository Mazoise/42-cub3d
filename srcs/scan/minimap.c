/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:22:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 21:25:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	int_to_img(t_mlx_img *img, unsigned int color, int i, int j)
{
	int		tmp;
	int		k;

	k = 0;
	tmp = (img->len * j + i * (img->bpp >> 3));
	while (k < img->bpp >> 3)
	{
		img->img[tmp + k] = color / pow(256, k);
		k++;
	}
}

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

void	pxl_map(t_params *params, t_idx idx, t_idx size)
{
	int		i;
	int		j;

	i = idx.i - params->max.i / 10;
	j = idx.j - params->max.j / 10;
	if (params->grid[(int)(j / size.j)][(int)(i / size.i)] == '1')
		int_to_img(&params->mini_m, 0xFFFFFF, idx.i, idx.j);
	else if (params->grid[(int)(j / size.j)][(int)(i / size.i)] == '0')
		int_to_img(&params->mini_m, 0xCCFFFFFF, idx.i, idx.j);
	else if (params->grid[(int)(j / size.j)][(int)(i / size.i)] == '2')
		int_to_img(&params->mini_m, 0x0000FF, idx.i, idx.j);
	else
		int_to_img(&params->mini_m, 0xFFFFFF, idx.i, idx.j);
}

int		draw_mini_map(t_params *params)
{
	t_idx		size;
	t_idx		idx;

	idx.i = params->max.i / 10;
	size.j = params->max.j - params->max.j / 5;
	size.i = params->max.i - params->max.i / 5;
	while (idx.i < params->max.i - params->max.i / 10)
	{
		idx.j = params->max.j / 10;
		while (idx.j < params->max.j - params->max.j / 10)
		{
			pxl_map(params, idx, size);
			idx.j++;
		}
		idx.i++;
	}
	mlx_put_image_to_window(params->ptr, params->wdw, params->minimap, 0, 0);
	return (1);
}
