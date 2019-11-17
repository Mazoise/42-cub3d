/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input_conversion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:11:22 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 14:09:33 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_mapstruct(t_map map)
{
	map.grid = 0;
	map.x_max = 0;
	map.y_max = 0;
	map.NO = 0;
	map.SO = 0;
	map.WE = 0;
	map.EA = 0;
	map.S = 0;
	map.F = 0;
	map.C = 0;
}