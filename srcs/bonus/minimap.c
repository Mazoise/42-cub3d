/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:22:05 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 11:50:25 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	player_map(t_params *params, t_idx idx, int box)
{
	int		i;
	int		j;
	t_pos	pct;

	pct.y = params->player.pos.x - floor(params->player.pos.x);
	pct.x = params->player.pos.y - floor(params->player.pos.y);
	i = pct.x * box - 4;
	while (i <= (int)(pct.x * box + 4))
	{
		j = pct.y * box - 4;
		while (j <= (int)(pct.y * box + 4))
		{
			rgb_to_img(&params->mini_m, params->bonus.colors.player, idx.i + i, idx.j + j);
			j++;
		}
		i++;
	}
}

void	pxl_map(t_params *params, t_idx idx, int box, char c)
{
	t_rgb	color;
	int		i;
	int		j;

	i = 0;
	if (c == '1')
		color = params->bonus.colors.one;
	else if (c == '0')
		color = params->bonus.colors.zero;
	else if (c == '2')
		color = params->bonus.colors.two;
	else if (c == 'p')
	{
		player_map(params, idx, box);
		return ;
	}
	else
		color = params->bonus.colors.out;
	while (i <= box)
	{
		j = 0;
		while (j <= box)
		{
			rgb_to_img(&params->mini_m, color, idx.i + i, idx.j + j);
			j++;
		}
		i++;
	}
}


int		draw_mini_map(t_params *params)
{
	double		size;
	int			diff;
	int			box;
	t_idx		idx;
	t_idx		inc;

	size = (params->max.j < params->max.i ? params->max.j - params->max.j / 5.0 : params->max.i - params->max.i / 5.0);
	diff = (ft_strlen(params->grid[0]) - ft_strslen(params->grid)) / 2;
	box = (ft_strlen(params->grid[0]) < ft_strslen(params->grid) ? ft_strslen(params->grid) : ft_strlen(params->grid[0]));
	box = size / box;
	inc.j = 0;
	idx.j = (params->max.j - size) / 2;
	idx.j = diff > 0 ? idx.j + abs(diff) * box : idx.j;
	while (params->grid[inc.j])
	{
		inc.i = 0;
		idx.i = (diff < 0 ? (params->max.i - size) / 2 + abs(diff) * box : (params->max.i - size) / 2);
		while (params->grid[inc.j][inc.i])
		{
			pxl_map(params, idx, box, params->grid[inc.j][inc.i]);
			if (inc.j == (int)params->player.pos.x && inc.i == (int)params->player.pos.y)
			{
				params->bonus.idx.i = idx.i;
				params->bonus.idx.j = idx.j;
			}
			inc.i++;
			idx.i += box;
		}
		inc.j++;
		idx.j += box;
	}
	pxl_map(params, params->bonus.idx, box, 'p');
	clear_void(&params->mini_m, params->max);
	mlx_put_image_to_window(params->ptr, params->wdw, params->minimap, 0, 0);
	return (1);
}
