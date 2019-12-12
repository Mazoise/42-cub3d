/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/12 10:40:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_grid(char c)
{
	if (c == '0' || c == '1' || c == '2')
		return (1);
	return (0);
}

int			is_compas(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int			pre_calc(t_params *params)
{
	if (params->max.i < 1 || params->max.j < 1)
	{
		ft_dprintf(2, "Error\nResolution must be at least 1 x 1\n");
		return (0);
	}
	if (params->max.i > FULLSCREEN_W)
		params->max.i = FULLSCREEN_W;
	if (params->max.j > FULLSCREEN_H)
		params->max.j = FULLSCREEN_H;
	params->calc.proj = (params->max.j / 2) / tan(M_PI / 6);
	return (1);
}

void		init_struct(t_params *params)
{
	params->grid = 0;
	params->max.i = -1;
	params->max.j = -1;
	params->graph.no.img = 0;
	params->graph.so.img = 0;
	params->graph.we.img = 0;
	params->graph.ea.img = 0;
	params->graph.s.img = 0;
	params->bonus.c.img = 0;
	params->bonus.f.img = 0;
	params->graph.f.true = 0;
	params->graph.c.true = 0;
	params->bonus.camh = 0;
	params->bonus.anim = 0;
	ft_memset(params->event, 0, EVENTS);
}
