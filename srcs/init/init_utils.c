/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:37:14 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/08 20:32:05 by mchardin         ###   ########.fr       */
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

void		pre_color(t_colors *colors)
{
	colors->one.blue = 255;
	colors->one.red = 255;
	colors->one.green = 255;
	colors->two.blue = 150;
	colors->two.red = 54;
	colors->two.green = 54;
	colors->zero.blue = 54;
	colors->zero.red = 54;
	colors->zero.green = 54;
	colors->out.blue = 0;
	colors->out.red = 0;
	colors->out.green = 0;
	colors->player.blue = 130;
	colors->player.red = 150;
	colors->player.green = 54;
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
	pre_color(&params->bonus.colors);
}
