/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:41:20 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 18:54:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

int		fill_grid(char *str, t_map *map)
{
	int		size;
	int		i;
	int		j;
	char	**temp_grid;

	i = 0;
	j = 0;
	temp_grid = map->grid;
	while (map->grid[size])
		size++;
	if (!(map->grid[0] = malloc(sizeof(char) * (size + 1))))
	{
		ft_printf("Error\nAllocation fail\n");
		free (map->grid);
		return (0);
	}
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			map->grid[0][j] = str[i];
		j++;
		i++;
	}
	map->grid[0][j] = 0;
	return (1);
}

int		first_fill_grid(char *str, t_map *map)
{
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(size = grid_width(str)))
		return (0);
	if (!(map->grid[0] = malloc(sizeof(char) * (size + 1))))
	{
		ft_printf("Error\nAllocation fail\n");
		free (map->grid);
		return (0);
	}
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			map->grid[0][j] = str[i];
		j++;
		i++;
	}
	map->grid[0][j] = 0;
	return (1);
}

int		conv_grid(char *str, t_map *map)
{
	if(!(check_all_params(map)))
		return (0);
	if (!map->grid)
	{
		if(!(map->grid = malloc(sizeof(char*) * 1)))
		{
			ft_printf("Error\nAllocation fail\n");
			return (0);
		}
		if (!(map->grid[0] = first_fill_grid(str, map)))
			return (0);
	}
	else
		if(!(fill_grid(str, map)))
			return (0);
	return (1);
}

int		conv_params(char *str, t_map *map)
{
	int		i;
	int		ret;

	i = 0;
	while (str[i] == ' ')
			i++;
		if (str[i] == 'R')
			ret = conv_resolution(str, map);
		else if (str[i] == 'S' || str[i] == 'N' || str[i] == 'W' || str[i] == 'E')
			ret = conv_texture(str, map);
		else if (str[i] == 'F' || str[i] == 'C')
			ret = conv_color(str, map);
		else
			ft_printf("Error\nWrong information syntax\n");
	}
}

int		convert_line(char *str, t_map *map)
{
	int		i;
	int		ret;

	i = 0;
	while(str[i] == ' ')
		i++;
	if (!(ft_is_digit(str[i])) && !(conv_params(str, map))
	{
		free(str);
		return (0);
	}
	else
		if(!(conv_grid(str, map)))
		{
			free(str);
			return (0);
		}
	free(str);
	return(1);
}

t_map	*read_map(char *mapcub)
{
	t_map	map;
	char	*str;
	int		fd;
	int		ret;
	
	if (!(check_format(mapcub)))
		return (0);
	else if ((fd = open(mapcub, O_RDONLY)) < 0)
	{
		ft_printf("Error\nDid not manage to open map file\n");
		return (0);
	}
	ft_init_mapstruct(&map);
	while ((ret = get_next_line(fd, &str)))
	{
		if (!(convert_line(str, &map)))
			return (0);
	}
	if (ret = -1)
	{
		ft_printf("Error\nAllocation fail\n");
		ft_free_grid(&map);
		return (0);
	}
	if (!map.grid)
	{
		ft_printf("Error\nNo map grid\n");
		return (0);
	}
}



		ft_printf("Refer to README.txt for more information\n");