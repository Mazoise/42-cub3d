/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initplayer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:16:41 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/27 12:13:29 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		first_line(char *str)
{
	int	last;

	last = 0;
	while (str[last] == '1')
		last++;
	if (last < 3)
	{
		ft_printf("Error\nInvalid map dimensions\n");
		return (0);
	}
	else if (str[last])
	{
		ft_printf("Error\nMap not closed on the north side\n");
		return (0);
	}
	return (last);
}

static int		closed_line(char *line, int *pos, int last)
{
	int j;

	if (line[0] != '1')
	{
		ft_printf("Error\nMap not closed on the west side\n");
		return (0);
	}
	j = -1;
	while (is_valid_grid_element(line[++j]))
		if (line[j] == 'N' || line[j] == 'S'
			|| line[j] == 'E' || line[j] == 'W')
			(*pos)++;
	if (j != last)
	{
		ft_printf("Error\nMap not rectangular\n");
		return (0);
	}
	if (line[j - 1] != '1')
	{
		ft_printf("Error\nMap not closed on the east side\n");
		return (0);
	}
	return (1);
}

static int		closed_grid(char **grid, int *pos)
{
	int		i;
	int		j;
	int		last;

	i = -1;
	if ((last = first_line(grid[0])) < 0)
		return (0);
	while (grid[++i])
		if (!(closed_line(grid[i], pos, last)))
			return (0);
	j = -1;
	while (grid[i - 1][++j])
	{
		if (grid[i - 1][j] != '1')
		{
			ft_printf("Error\nMap not closed on the south side\n");
			return (0);
		}
	}
	return (1);
}

static int		player_start(char *c, t_player *player, int i, int j)
{
	if (*c == 'N' || *c == 'S'
				|| *c == 'E' || *c == 'W')
	{
		player->pos.x = (double)i + 0.5;
		player->pos.y = (double)j + 0.5;
		if (*c == 'N')
			player->compas = M_PI;
		else if (*c == 'S')
			player->compas = 0;
		else if (*c == 'E')
			player->compas = M_PI / 2;
		else if (*c == 'W')
			player->compas = (3 * M_PI) / 2;
		*c = '0';
		return (1);
	}
	return (0);
}

int				init_player(t_player *player, char **grid)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	pos = 0;
	if (!(closed_grid(grid, &pos)))
		return (0);
	if (pos != 1)
	{
		ft_printf("Error\nNo multi player mode available on this game\n");
		return (0);
	}
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (player_start(&grid[i][j], player, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
