/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:34:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 11:10:52 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		walk_here(t_pos dir, t_pos hit, t_pos *pos, t_params *params)
{
	(void)params;
	(void)hit;
	pos->x = dir.x;
	pos->y = dir.y;
}

int			check_all_params(t_params *params)
{
	int ret;

	ret = 0;
	if ((params->max.i < 0 || params->max.j < 0))
		ret = ft_dprintf(2, "Error\nMissing resolution format\n");
	if (!params->graph.no.img)
		ret = ft_dprintf(2, "Error\nMissing north texture path\n");
	if (!params->graph.so.img)
		ret = ft_dprintf(2, "Error\nMissing south texture path\n");
	if (!params->graph.we.img)
		ret = ft_dprintf(2, "Error\nMissing west texture path\n");
	if (!params->graph.ea.img)
		ret = ft_dprintf(2, "Error\nMissing east texture path\n");
	if (!params->graph.s.img)
		ret = ft_dprintf(2, "Error\nMissing sprite texture path\n");
	if (!params->graph.f.true)
		ret = ft_dprintf(2, "Error\nMissing floor color format\n");
	if (!params->graph.c.true)
		ret = ft_dprintf(2, "Error\nMissing ceiling color format\n");
	return (ret);
}

void		line_put(t_params *params, double inc, int i, double angle)
{
	double	dist;
	double	height;
	t_pos	power;
	t_idx	idx;
	double	pct;

	(void)angle;
	idx.i = i;
	idx.j = -1;
	power.x = pow(params->scan.wall.x - params->player.pos.x, 2);
	power.y = pow(params->scan.wall.y - params->player.pos.y, 2);
	dist = cos(inc) * rsqrt(power.x + power.y);
	height = params->max.i / (dist * params->max.j) * params->calc.proj;
	while (++idx.j < (params->max.j - height) / 2)
		rgb_to_img(&params->img, params->graph.c, idx.i, idx.j);
	pct = pct_calc(params);
	texture_put(params, height, pct, &idx);
	while (idx.j < params->max.j)
		rgb_to_img(&params->img, params->graph.f, idx.i, idx.j++);
}

void		sprite_put(t_params *params, double height, double pct, t_idx *idx)
{
	int			k;
	int			end;
	double		tmp;
	double		tmp2;

	if (height > params->max.j)
	{
		k = (height - params->max.j) / 2;
		end = params->max.j + (height - params->max.j) / 2;
	}
	else
	{
		k = 0;
		end = height;
	}
	while (k < end)
	{
		tmp = floor(k * params->scan.face->h / height) + pct;
		tmp = tmp * params->scan.face->w;
		tmp2 = (params->img.len * idx->j + idx->i * (params->img.bpp >> 3));
		add_pix(&params->img, params->scan.face->txtr, tmp2, tmp);
		idx->j++;
		k++;
	}
}
