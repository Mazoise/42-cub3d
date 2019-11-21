/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:16:41 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/21 11:06:28 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			closed_grid(char **grid)
{
	int		i;
	int		j;
	int		last;
	int		pos;

	i = 0;
	last = 0;
	pos = 0;
	while (grid[0][last] == '1')
		last++;
	if (grid[0][last])
		return (0);
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][0] != '1')
				return (0);
			while (is_valid_grid_element(grid[i][j]))
			{
				if (grid[i][j] == 'N' || grid[i][j] == 'S'
					|| grid[i][j] == 'E'|| grid[i][j] == 'W')
					pos++;
				j++;
			}
			if (j != last || grid[i][j - 1] != '1')
				return (0);
		}
		i++;
	}
	j = 0;
	while (grid[i - 1][j])
	{
		if (grid[i - 1][j] != '1')
			return (0);
		j++;
	}
	if (pos != 1)
		return (0);
	return (1);
}

int			check_n_pos(t_player *player, char **grid)
{
	int		i;
	int		j;

	i = 0;
	if (!(closed_grid(grid)))
	{
		ft_printf("Map error grid\n");
		return (0);
	}
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
			{
				player->pos.x = (double)i + 0.5;
				player->pos.y = (double)j + 0.5;
				if (grid[i][j] == 'N')
					player->compas = 90;
				else if (grid[i][j] == 'S')
					player->compas = 270;
				else if (grid[i][j] == 'E')
					player->compas = 0;
				else if (grid[i][j] == 'W')
					player->compas = 180;
				grid[i][j] = '0';
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int		init_player(t_params *params)
{
	if(!(check_n_pos(&params->player, params->grid)))
	{
		ft_printf("Map error\n");
		return (0);
	}	
	return (1);
}
