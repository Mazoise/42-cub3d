/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:34:54 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/10 11:12:34 by mchardin         ###   ########.fr       */
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
	if (!params->graph.NO.img)
		ret = ft_dprintf(2, "Error\nMissing north texture path\n");
	if (!params->graph.SO.img)
		ret = ft_dprintf(2, "Error\nMissing south texture path\n");
	if (!params->graph.WE.img)
		ret = ft_dprintf(2, "Error\nMissing west texture path\n");
	if (!params->graph.EA.img)
		ret = ft_dprintf(2, "Error\nMissing east texture path\n");
	if (!params->graph.S.img)
		ret = ft_dprintf(2, "Error\nMissing sprite texture path\n");
	if (!params->graph.F.true)
		ret = ft_dprintf(2, "Error\nMissing floor color format\n");
	if (!params->graph.C.true)
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
		rgb_to_img(&params->img, params->graph.C, idx.i, idx.j);
	pct = pct_calc(params);
	texture_put(params, height, pct, &idx);
	while (idx.j < params->max.j)
		rgb_to_img(&params->img, params->graph.F, idx.i, idx.j++);
}
