/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/07 15:55:09 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_memset(params->event, 0, EVENTS);
}

void		check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Error\nNo map specified\n");
		exit(0);
	}
	else if (argc > 3)
	{
		ft_dprintf(2, "Error\nToo many arguments\n");
		exit(0);
	}
	else if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "-save", 6))
			params->screenshot = 1;
		else
		{
			ft_dprintf(2, "Error\nTo take a screenshot add \"-save\"\n");
			exit(0);
		}
	}
	else
		params->screenshot = 0;
}

int			initialisation(char *mapcub, t_params *params)
{
	init_struct(params);
	if (!(read_map(mapcub, params)))
		return (0);
	if (!(init_player(&params->player, params->grid)))
		return (0);
	pre_calc(params);
	return (1);
}
