/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/11 13:21:31 by mchardin         ###   ########.fr       */
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

void		pre_calc(t_params *params)
{
	if (params->max.i > FULLSCREEN_W)
		params->max.i = FULLSCREEN_W;
	if (params->max.j > FULLSCREEN_H)
		params->max.j = FULLSCREEN_H;
	params->calc.proj = (params->max.j / 2) / tan(M_PI / 6);
}

void		init_struct(t_params *params)
{
	params->grid = 0;
	params->max.i = -1;
	params->max.j = -1;
	params->graph.NO.img = 0;
	params->graph.SO.img = 0;
	params->graph.WE.img = 0;
	params->graph.EA.img = 0;
	params->graph.S.img = 0;
	params->bonus.C.img = 0;
	params->bonus.F.img = 0;
	params->graph.F.true = 0;
	params->graph.C.true = 0;
	params->bonus.camh = 0;
	params->bonus.anim = 0;
	ft_memset(params->event, 0, EVENTS);
}
