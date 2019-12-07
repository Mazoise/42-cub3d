/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 20:53:54 by mchardin         ###   ########.fr       */
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
	params->calc.step = 0.1;
	params->calc.turn = 0.05;
}
