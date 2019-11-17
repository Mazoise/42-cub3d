/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 10:41:20 by mchardin          #+#    #+#             */
/*   Updated: 2019/11/17 22:19:18 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <fcntl.h>

int		fill_grid(char *str, t_map *map)
{
	int			size;
	int			add;
	size_t		i;
	size_t		j;
	char		**temp_grid;

	i = 0;
	j = 0;
	size = 0;
	temp_grid = map->grid;
	while (map->grid[size])
		size++;
	if (!(map->grid = malloc(sizeof(char*) * (size + 1))))
	{
		ft_printf("Error\nAllocation fail\n");
		free_grid(temp_grid);
		return (0);
	}
	map->grid[size + 1] = 0;
	add = size;
	if (!(map->grid[size] = malloc(sizeof(char) * (ft_strlen(temp_grid[0]) + 1))))
	{
		ft_printf("Error\nAllocation fail\n");
		free_grid(temp_grid);
		free(map->grid);
		return (0);
	}
	size--;
	while (size >= 0)
	{
		temp_grid[size] = map->grid[size];
		size--;
	}
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (str[i])
			map->grid[add][j] = str[i];
		j++;
		i++;
	}
	map->grid[0][j] = 0;
	if (j != ft_strlen(temp_grid[0]))
	{
		ft_printf("Error\nAllocation fail\n");
		free_grid(map->grid);
		free(temp_grid);
		return (0);
	}
	free(temp_grid);
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
		if(!(map->grid = malloc(sizeof(char*) * 2)))
		{
			ft_printf("Error\nAllocation fail\n");
			return (0);
		}
		if (!(first_fill_grid(str, map)))
			return (0);
		map->grid[1] = 0;
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
	ret = 0;
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
	return (ret);
}

int		convert_line(char *str, t_map *map)
{
	int		i;

	i = 0;
	while(str[i] == ' ')
		i++;
	if (!(ft_isdigit(str[i])) && !(conv_params(str, map)))
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
	t_map	*map;
	char	*str;
	int		fd;
	int		ret;
	
	map = 0;
	if (!(check_format(mapcub)))
		return (0);
	else if ((fd = open(mapcub, O_RDONLY)) < 0)
	{
		ft_printf("Error\nDid not manage to open map file\n");
		return (0);
	}
	if (!(init_mapstruct(map)))
	{
		ft_printf("Error\nAllocation fail\n");
		return (0);
	}
	while ((ret = get_next_line(fd, &str)))
	{
		if (!(convert_line(str, map)))
			return (0);
	}
	if (!(convert_line(str, map)))
			return (0);
	if (ret == -1)
	{
		ft_printf("Error\nAllocation fail\n");
		free_grid(map->grid);
		return (0);
	}
	if (!map->grid)
	{
		ft_printf("Error\nNo map grid\n");
		return (0);
	}
	return (map);
}

		// ft_printf("Refer to README.txt for more information\n");