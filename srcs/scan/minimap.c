/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:22:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 22:00:09 by mchardin         ###   ########.fr       */
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

void	pxl_map(t_params *params, t_idx idx, t_pos size)
{
	t_pos	pos;
	t_idx	len;

	len.j = ft_strlen(params->grid[0]);
	len.i = ft_strslen(params->grid);
	pos.x = idx.i - params->max.i / 10.0;
	pos.y = idx.j - params->max.j / 10.0;
	if (params->grid[(int)(len.i * pos.y / size.y)][(int)(len.j * pos.x / size.x)] == '1')
		int_to_img(&params->mini_m, 0xFFFFFF, idx.i, idx.j);
	else if (params->grid[(int)(len.i * pos.y / size.y)][(int)(len.j * pos.x / size.x)] == '0')
		int_to_img(&params->mini_m, 0xFFFFFFBB, idx.i, idx.j);
	else if (params->grid[(int)(len.i * pos.y / size.y)][(int)(len.j * pos.x / size.x)] == '2')
		int_to_img(&params->mini_m, 0x0000FF, idx.i, idx.j);
	else
		int_to_img(&params->mini_m, 0xFFFFFF, idx.i, idx.j);
}

int		draw_mini_map(t_params *params)
{
	t_pos		size;
	t_idx		idx;

	idx.i = params->max.i / 10;
	size.y = params->max.j - params->max.j / 5.0;
	size.x = params->max.i - params->max.i / 5.0;
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
