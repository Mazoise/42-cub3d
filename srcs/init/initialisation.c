/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/28 23:04:08 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_printf("Error\nNo map specified\n");
		return (0);
	}
	else if (argc > 3)
	{
		ft_printf("Error\nToo many arguments\n");
		return (0);
	}
	else if (argc == 3 && is_save_request(argv[2]))
		params->screenshot = 1;
	else
		params->screenshot = 0;
	return (1);
}

void		pre_calc(t_params *params)
{
	params->calc.proj = (params->max.j / 2) / tan(M_PI / 6);
}

int			initialisation(char *mapcub, t_params *params)
{
	init_struct(params);
	if (!(read_map(mapcub, params)))
	{
		ft_printf("READMAP ERROR\n");
		return (0);
	}
	if (!(init_player(&params->player, params->grid)))
	{
		ft_printf("INITPLAYER ERROR\n");
		return (0);
	}
	pre_calc(params);
	return (1);
}
