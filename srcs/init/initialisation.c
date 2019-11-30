/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/30 10:15:36 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_printf("Error\nNo map specified\n");
		exit (0);
	}
	else if (argc > 3)
	{
		ft_printf("Error\nToo many arguments\n");
		exit (0);
	}
	else if (argc == 3)
	{
		if (!ft_strncmp(argv[2], "-save", 6))
			params->screenshot = 1;
		else
		{
			ft_printf("Error\nTo take a screenshot add \"-save\"\n");
			exit (0);
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
