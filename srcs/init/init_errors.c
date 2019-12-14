/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 19:12:35 by mchardin          #+#    #+#             */
/*   Updated: 2019/12/14 10:42:31 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_format(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (!ft_strncmp(str, "-save", 6))
	{
		ft_dprintf(2, "Error\nMissing map reference before save request\n");
		exit(0);
	}
	else if (i < 5 || ft_strncmp(&str[i - 4], ".cub", 5))
	{
		ft_dprintf(2, "Error\nMap file should end in \".cub\"\n");
		exit(0);
	}
}

void		check_args(int argc, char **argv, t_params *params)
{
	if (argc < 2)
	{
		ft_dprintf(2, "Error\nNo map specified\n");
		exit(0);
	}
	else if (argc > 2 && (!ft_strncmp(argv[2], "-save", 6)
		|| !ft_strncmp(argv[2], "--save", 7)))
		params->screenshot = 1;
	else
		params->screenshot = 0;
}

void		txtr_error(char c)
{
	if (c == 'N')
		ft_dprintf(2, "(north texture)\n");
	else if (c == 'S')
		ft_dprintf(2, "(south texture)\n");
	else if (c == 'E')
		ft_dprintf(2, "(east texture)\n");
	else if (c == 'W')
		ft_dprintf(2, "(west texture)\n");
	else if (c == 'F')
		ft_dprintf(2, "(floor texture)\n");
	else if (c == 'C')
		ft_dprintf(2, "(ceiling texture)\n");
	else
		ft_dprintf(2, "(sprite texture)\n");
}

void		player_error(int pos)
{
	if (pos > 1)
		ft_dprintf(2, "Error\nNo multi player mode available on this game\n");
	else if (pos < 1)
		ft_dprintf(2, "Error\nMissing starting point in map\n");
}

int			error_conv(char c)
{
	if (c == 'F')
		ft_dprintf(2, "Error\nMultiple definition (floor)\n");
	else if (c == 'C')
		ft_dprintf(2, "Error\nMultiple definition (ceiling)\n");
	else if (c)
		ft_dprintf(2, "Error\nWrong information syntax\n");
	return (0);
}
